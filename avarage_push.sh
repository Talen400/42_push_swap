#!/bin/bash
#
# Comprehensive script to test push_swap performance and efficiency.
# Calculates the average number of operations over N tests and provides a detailed analysis
# of the last successful case.
#

# --- CONFIGURATION ---
PUSH_SWAP_PATH="./push_swap"
CHECKER_PATH="./checker"
NUM_OF_ELEMENTS=500
NUM_OF_TESTS=500
MAX_VALUE=10000
VALIDATE_OUTPUT=true # Change to true to validate with checker
TIMEOUT_SECONDS=5
# --------------------

TOTAL_OPERATIONS=0
SUCCESS_COUNT=0
declare -a RESULTS
LAST_OPS_FILE="last_run_ops.txt" # Temporary file for the last successful test

# Colors for output (optional)
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Check executable
if [ ! -x "$PUSH_SWAP_PATH" ]; then
    echo -e "${RED}Error: '$PUSH_SWAP_PATH' not found${NC}"
    exit 1
fi

# Function to generate a list of unique, random numbers
generate_list() {
    if command -v shuf &> /dev/null; then
        seq 1 $MAX_VALUE | shuf -n $1 | tr '\n' ' '
    elif command -v gshuf &> /dev/null; then
        seq 1 $MAX_VALUE | gshuf -n $1 | tr '\n' ' '
    else
        # Fallback: slower
        seq 1 $MAX_VALUE | sort -R | head -n $1 | tr '\n' ' '
    fi
}

echo "--- Push_Swap Comprehensive Tester ---"
echo "Elements: $NUM_OF_ELEMENTS | Tests: $NUM_OF_TESTS"
echo "--------------------------------------"

# Test loop
for ((i=1; i<=$NUM_OF_TESTS; i++)); do
    RANDOM_LIST=$(generate_list $NUM_OF_ELEMENTS)
    
    # 1. Execute with timeout and capture operations
    # Capture stderr to a temporary file to check for crashes/errors (e.g., segfaults)
    ERR_LOG=$(mktemp)
    OPERATIONS=$(timeout ${TIMEOUT_SECONDS}s $PUSH_SWAP_PATH $RANDOM_LIST 2> $ERR_LOG)
    EXIT_CODE=$?
    
    # Check for Execution Errors (Crash/Segfault)
    if [ $EXIT_CODE -ne 0 ] && [ $EXIT_CODE -ne 124 ]; then
        echo -e "\n${RED}❌ Test $i: EXECUTION ERROR (Code $EXIT_CODE)!${NC}"
        echo -e "${RED}FAILING INPUT: $RANDOM_LIST${NC}"
        # Print any actual stderr output from the program (like a segmentation fault message)
        [ -s $ERR_LOG ] && echo -e "${YELLOW}--- Stderr Output ---\n$(cat $ERR_LOG)\n---------------------${NC}"
        rm $ERR_LOG
        continue
    elif [ $EXIT_CODE -eq 124 ]; then
        echo -e "${YELLOW}Warning: Test $i timed out${NC}"
        rm $ERR_LOG
        continue
    fi
    
    rm $ERR_LOG
    
    OP_COUNT=$(echo "$OPERATIONS" | wc -l | tr -d '[:space:]')
    
    # 2. Validate with checker (optional)
    if [ "$VALIDATE_OUTPUT" = true ] && [ -x "$CHECKER_PATH" ]; then
        # The checker itself should be silent, so redirect its stderr
        RESULT=$(echo "$OPERATIONS" | $CHECKER_PATH $RANDOM_LIST 2>/dev/null)
        
        if [ "$RESULT" != "OK" ]; then
            echo -e "\n${RED}❌ Test $i FAILED CHECKER verification! Result: $RESULT${NC}"
            echo -e "${RED}FAILING INPUT: $RANDOM_LIST${NC}"
            continue
        fi
    fi
    
    # 3. Accumulate results and save output for detailed analysis
    if [[ "$OP_COUNT" =~ ^[0-9]+$ ]] && [ $OP_COUNT -gt 0 ]; then
        TOTAL_OPERATIONS=$((TOTAL_OPERATIONS + OP_COUNT))
        RESULTS+=($OP_COUNT)
        SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
        
        # Saves the output of this test to the temporary file for final analysis
        echo "$OPERATIONS" > $LAST_OPS_FILE
        
        echo -ne "Test $i/$NUM_OF_TESTS: $OP_COUNT ops\r"
    else
        echo -e "${YELLOW}Warning: Test $i invalid${NC}"
    fi
done

echo "" # Newline

# --- GENERAL STATISTICS ---
if [ $SUCCESS_COUNT -gt 0 ]; then
    AVERAGE=$(echo "scale=2; $TOTAL_OPERATIONS / $SUCCESS_COUNT" | bc)
    
    # Min/Max
    MIN=${RESULTS[0]}
    MAX=${RESULTS[0]}
    for val in "${RESULTS[@]}"; do
        (( val < MIN )) && MIN=$val
        (( val > MAX )) && MAX=$val
    done
    
    echo "--------------------------------------"
    echo -e "${GREEN}✅ Average Tests: $SUCCESS_COUNT/$NUM_OF_TESTS${NC}"
    echo "Average: $AVERAGE ops"
    echo "Minimum: $MIN ops"
    echo "Maximum: $MAX ops"
    echo "Variance (Range): $((MAX - MIN)) ops"
    echo "--------------------------------------"
    
    # --- DISTRIBUTION ANALYSIS (Last Test) ---
    if [ -f "$LAST_OPS_FILE" ]; then
        echo -e "${CYAN}=== DISTRIBUTION ANALYSIS (Last Test) ===${NC}"
        
        OPS_TOTAL=$(wc -l < $LAST_OPS_FILE | tr -d '[:space:]')
        echo "Total: $OPS_TOTAL ops"
        echo ""
        echo "Distribution:"
        echo "pa:  $(grep -c '^pa$' $LAST_OPS_FILE)"
        echo "pb:  $(grep -c '^pb$' $LAST_OPS_FILE)"
        echo "ra:  $(grep -c '^ra$' $LAST_OPS_FILE)"
        echo "rra: $(grep -c '^rra$' $LAST_OPS_FILE)"
        echo "rb:  $(grep -c '^rb$' $LAST_OPS_FILE)"
        echo "rrb: $(grep -c '^rrb$' $LAST_OPS_FILE)"
        echo "sa:  $(grep -c '^sa$' $LAST_OPS_FILE)"
        echo "sb:  $(grep -c '^sb$' $LAST_OPS_FILE)"
        echo "ss:  $(grep -c '^ss$' $LAST_OPS_FILE)"
        echo ""
        echo -e "${YELLOW}🔥 OPTIMIZATIONS (CRITICAL):${NC}"
        echo "rr:  $(grep -c '^rr$' $LAST_OPS_FILE)  "
        echo "rrr: $(grep -c '^rrr$' $LAST_OPS_FILE) "
        echo "--------------------------------------"

        # Clean up temporary file
        rm $LAST_OPS_FILE 2>/dev/null
    fi
else
    echo -e "${RED}No successful tests${NC}"
    exit 1
fi

