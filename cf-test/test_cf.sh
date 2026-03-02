#!/bin/bash

# Test cf-tool with provided credentials
USERNAME="hellohellohellohello"
PASSWORD="#A9*tMPdWvkdwk4tP7Lc"

echo "=== Testing cf-tool ==="
echo ""

# Check if cf binary exists and is executable
echo "1. Checking cf binary..."
which cf
cf --version || cf -h | head -5
echo ""

# Create config file as per the workflow
echo "2. Creating config file..."
mkdir -p ~/.config/cf
touch ~/.config/cf/config

# The workflow writes these three lines - we need to figure out what ONE, TWO, THREE are
echo "cpp=61" > ~/.config/cf/config
echo ""

# Try to login
echo "3. Attempting login..."
echo "This will try interactive login..."
echo ""

# Show help to understand available commands
echo "4. Available cf-tool commands:"
cf -h
echo ""

echo "=== Test Complete ==="
echo ""
echo "To manually test login, run:"
echo "  cf config"
echo "or"
echo "  cf login"


