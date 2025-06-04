#!/bin/bash

# ========== Colors ==========
OK_COLOR="\033[1;32m"
KO_COLOR="\033[1;31m"
INFO_COLOR="\033[1;34m"
WARN_COLOR="\033[1;33m"
RESET_COLOR="\033[0m"

# ========== Paths ==========
MINISHELL="./minishell"
BASH="/bin/bash"
TEST_DIR="tests"
RESULTS_DIR="results"

# ========== Rebuild ==========
echo -e "${INFO_COLOR}Rebuilding minishell...${RESET_COLOR}"
make re >/dev/null 2>&1
if [[ $? -ne 0 || ! -x $MINISHELL ]]; then
    echo -e "${KO_COLOR}Build failed or minishell binary not found!${RESET_COLOR}"
    exit 1
fi

# ========== Test Loop ==========
mkdir -p "$RESULTS_DIR"

for test_file in "$TEST_DIR"/*; do
    name=$(basename "$test_file")
    result_path="$RESULTS_DIR/$name"
    mkdir -p "$result_path"

    # Run minishell
    <"$test_file" "$MINISHELL" >"$result_path/mini" 2>&1
    mini_status=$?

    # Run bash
    <"$test_file" $BASH >"$result_path/bash" 2>&1
    bash_status=$?

    # Compare output
    diff_output=$(diff -u "$result_path/mini" "$result_path/bash")
    if [[ $mini_status -eq $bash_status && -z "$diff_output" ]]; then
        echo -e "${OK_COLOR}test $name OK${RESET_COLOR}"
        rm -rf "$result_path"
    else
        echo -e "${KO_COLOR}test $name KO${RESET_COLOR}"
        if [[ $mini_status -ne $bash_status ]]; then
            echo -e "${WARN_COLOR}exit status: minishell=$mini_status, bash=$bash_status${RESET_COLOR}" \
                | tee "$result_path/status"
        fi
        if [[ -n "$diff_output" ]]; then
            echo "$diff_output" >"$result_path/diff"
            echo -e "${INFO_COLOR}diff:${RESET_COLOR}"
            echo "$diff_output"
        fi
    fi
done
