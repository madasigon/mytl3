#!/bin/bash

USERNAME="hellohellohellohello"
PASSWORD="#A9*tMPdWvkdwk4tP7Lc"

echo "=== Automated cf-tool Login Test ==="
echo ""

# Try to login with the credentials
# The tool expects interactive input, so we'll use expect-like behavior
echo "Attempting login as: $USERNAME"
echo ""

# First, let's see what the login process looks like
# We'll answer 'y' to store the password
(echo "y"; echo "$PASSWORD") | cf login "$USERNAME"

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Login successful!"
    echo ""
    echo "Testing submission capability..."
    echo "Checking config:"
    cat ~/.config/cf/config 2>/dev/null || echo "No config file found"
else
    echo ""
    echo "✗ Login failed!"
    exit 1
fi


