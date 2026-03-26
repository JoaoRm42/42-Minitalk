#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR" || exit 1

pass=0
fail=0

report() {
  local name="$1"
  local ok="$2"
  local info="$3"
  if [ "$ok" = "1" ]; then
    echo "[PASS] $name - $info"
    pass=$((pass + 1))
  else
    echo "[FAIL] $name - $info"
    fail=$((fail + 1))
  fi
}

rm -f /tmp/mt_server_out.txt /tmp/mt_client_out.txt /tmp/mt_err1.txt /tmp/mt_err2.txt /tmp/mt_err3.txt
./server > /tmp/mt_server_out.txt 2>&1 &
SPID=$!
sleep 0.2

# T1 basic
./client "$SPID" "Hello42" >> /tmp/mt_client_out.txt 2>&1
sleep 0.2
if grep -q "Hello42" /tmp/mt_server_out.txt; then
  report "T1 basic" 1 "message printed"
else
  report "T1 basic" 0 "message missing"
fi

# T2 empty message
./client "$SPID" "" >> /tmp/mt_client_out.txt 2>&1
RC=$?
if [ $RC -eq 0 ]; then
  report "T2 empty" 1 "exit=$RC"
else
  report "T2 empty" 0 "exit=$RC"
fi

# T3 long
LONG=$(head -c 4000 < /dev/zero | tr '\0' 'A')
./client "$SPID" "$LONG" >> /tmp/mt_client_out.txt 2>&1
RC=$?
sleep 0.5
if [ $RC -eq 0 ] && grep -q "AAAAAA" /tmp/mt_server_out.txt; then
  report "T3 long" 1 "4000 chars sent"
else
  report "T3 long" 0 "send failed or not visible"
fi

# T4 sequential burst
ok=1
for i in $(seq 1 120); do
  ./client "$SPID" "m$i" >> /tmp/mt_client_out.txt 2>&1 || ok=0
done
sleep 0.5
report "T4 sequential burst" "$ok" "120 messages"

# T5 invalid format (argc)
./client > /tmp/mt_err1.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "wrong format" /tmp/mt_err1.txt; then
  report "T5 argc" 1 "proper error"
else
  report "T5 argc" 0 "unexpected behavior"
fi

# T6 invalid pid alpha
./client abc test > /tmp/mt_err2.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "invalid PID" /tmp/mt_err2.txt; then
  report "T6 invalid pid" 1 "proper error"
else
  report "T6 invalid pid" 0 "unexpected behavior"
fi

# T7 unavailable pid
./client 999999 test > /tmp/mt_err3.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "PID not available" /tmp/mt_err3.txt; then
  report "T7 unavailable pid" 1 "proper error"
else
  report "T7 unavailable pid" 0 "unexpected behavior"
fi

# T8 concurrent clients (destructive)
PIDS=""
for i in $(seq 1 8); do
  ./client "$SPID" "C$i" >> /tmp/mt_client_out.txt 2>&1 &
  PIDS="$PIDS $!"
done
for p in $PIDS; do
  wait "$p"
done
sleep 0.5
hits=$(grep -o "C[1-8]" /tmp/mt_server_out.txt | wc -l)
if [ "$hits" -ge 4 ]; then
  report "T8 concurrent" 1 "partial/total delivery hits=$hits"
else
  report "T8 concurrent" 0 "too much corruption hits=$hits"
fi

kill "$SPID" 2>/dev/null || true
wait "$SPID" 2>/dev/null || true

bytes=$(wc -c < /tmp/mt_server_out.txt)
echo "---"
echo "Mandatory stress summary: pass=$pass fail=$fail server_bytes=$bytes"
