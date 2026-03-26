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

rm -f /tmp/mtb_server_out.txt /tmp/mtb_client_out.txt /tmp/mtb_err1.txt /tmp/mtb_err2.txt /tmp/mtb_err3.txt
./server > /tmp/mtb_server_out.txt 2>&1 &
SPID=$!
sleep 0.2

# B1 basic with delivery confirmation
OUT=$(./client "$SPID" "HelloBonus" 2>&1)
RC=$?
echo "$OUT" >> /tmp/mtb_client_out.txt
sleep 0.2
if [ $RC -eq 0 ] && echo "$OUT" | grep -q "Message received by server" && grep -q "HelloBonus" /tmp/mtb_server_out.txt; then
  report "B1 basic+ack" 1 "delivery confirmed"
else
  report "B1 basic+ack" 0 "ack/message mismatch"
fi

# B2 long message (600 chars)
LONG=$(head -c 600 < /dev/zero | tr '\0' 'B')
OUT=$(./client "$SPID" "$LONG" 2>&1)
RC=$?
echo "$OUT" >> /tmp/mtb_client_out.txt
sleep 0.2
if [ $RC -eq 0 ] && echo "$OUT" | grep -q "Message received by server"; then
  report "B2 long" 1 "600 chars + ack"
else
  report "B2 long" 0 "failed long transfer"
fi

# B3 sequential burst 40
ok=1
for i in $(seq 1 40); do
  OUT=$(./client "$SPID" "b$i" 2>&1) || ok=0
  echo "$OUT" >> /tmp/mtb_client_out.txt
  echo "$OUT" | grep -q "Message received by server" || ok=0
done
report "B3 sequential burst" "$ok" "40 acked messages"

# B4 invalid argc
./client > /tmp/mtb_err1.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "wrong format" /tmp/mtb_err1.txt; then
  report "B4 argc" 1 "proper error"
else
  report "B4 argc" 0 "unexpected behavior"
fi

# B5 invalid pid alpha
./client abc test > /tmp/mtb_err2.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "invalid PID" /tmp/mtb_err2.txt; then
  report "B5 invalid pid" 1 "proper error"
else
  report "B5 invalid pid" 0 "unexpected behavior"
fi

# B6 unavailable pid
./client 999999 test > /tmp/mtb_err3.txt 2>&1
RC=$?
if [ $RC -ne 0 ] && grep -q "PID not available" /tmp/mtb_err3.txt; then
  report "B6 unavailable pid" 1 "proper error"
else
  report "B6 unavailable pid" 0 "unexpected behavior"
fi

# B7 destructive concurrent clients (timeout protected)
ok=1
PIDS=""
for i in $(seq 1 4); do
  timeout 3 ./client "$SPID" "X$i" >> /tmp/mtb_client_out.txt 2>&1 &
  PIDS="$PIDS $!"
done
for p in $PIDS; do
  wait "$p" || ok=0
done
if [ "$ok" = "1" ]; then
  report "B7 concurrent" 1 "all concurrent clients returned"
else
  report "B7 concurrent" 0 "timeouts/errors under concurrency"
fi

kill "$SPID" 2>/dev/null || true
wait "$SPID" 2>/dev/null || true

bytes=$(wc -c < /tmp/mtb_server_out.txt)
echo "---"
echo "Bonus stress summary: pass=$pass fail=$fail server_bytes=$bytes"
