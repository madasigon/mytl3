# CF-Tool Docker Setup Guide

This setup provides a complete cf-tool environment with all dependencies in a Docker container.

## What's Included

- Ubuntu latest base image
- Go 1.25.7 (latest)
- Node.js 20.x with npm and pnpm
- mcp-chrome-bridge (for browser mode)
- cf-tool (built from source)

## Quick Start

### Option 1: Using Docker Compose (Recommended)

```bash
# Build and start the container
docker-compose -f docker-compose.cf-tool.yml up -d

# Enter the container
docker exec -it cf-tool-env bash

# Inside container, verify installations
go version
node --version
pnpm --version
cf --version

# mcp-chrome-bridge should already be running
# Check with: ps aux | grep mcp-chrome-bridge
```

### Option 2: Using Docker directly

```bash
# Build the image
docker build -f Dockerfile.cf-tool -t cf-tool:latest .

# Run the container
docker run -it -p 12306:12306 -v $(pwd):/workspace cf-tool:latest bash

# Inside container, verify installations
cf --version
```

## Using cf-tool

### Setup Chrome Extension (One-time setup)

**Important:** You need to install the mcp-chrome extension in your **host machine's Chrome browser**, not inside Docker.

1. Download [mcp-chrome extension](https://github.com/hangwin/mcp-chrome/)
2. Extract to a folder on your host machine
3. Open Chrome and go to `chrome://extensions/`
4. Enable "Developer mode"
5. Click "Load unpacked" and select the extension folder
6. The extension should connect to `http://127.0.0.1:12306/mcp` (which is forwarded from the container)

### Verify Setup

Inside the container:

```bash
# Test MCP connection
cf mcp-ping

# Test browser automation
cf mocka
```

### Common cf-tool Commands

```bash
# Parse a contest (e.g., contest 1234)
cf parse 1234

# Parse a specific problem
cf parse 1234a

# Test your solution
cf test

# Submit your solution
cf submit

# Open problem in browser
cf open

# Race mode (countdown + auto-parse)
cf race 1234
```

## Troubleshooting

### mcp-chrome-bridge not running

If the bridge isn't running inside the container:

```bash
# Start it manually
mcp-chrome-bridge &

# Or check logs
ps aux | grep mcp-chrome-bridge
```

### Chrome extension shows "Service Not Started"

1. Make sure the container is running: `docker ps`
2. Check port forwarding: `docker port cf-tool-env`
3. Restart the container: `docker-compose -f docker-compose.cf-tool.yml restart`

### cf mcp-ping fails

1. Ensure mcp-chrome-bridge is running in the container
2. Ensure Chrome extension is installed and enabled on host
3. Check that port 12306 is properly forwarded

## Architecture

```
Host Machine (Chrome Browser + Extension)
    ↓ (connects to localhost:12306)
Docker Container (mcp-chrome-bridge + cf-tool)
    ↓ (controls browser via Chrome DevTools Protocol)
Chrome Browser (performs actual web automation)
```

## Stopping the Container

```bash
# Stop the container
docker-compose -f docker-compose.cf-tool.yml down

# Or if using docker directly
docker stop cf-tool-env
```

## Rebuilding

If you need to rebuild (e.g., to get latest cf-tool updates):

```bash
# Using docker-compose
docker-compose -f docker-compose.cf-tool.yml build --no-cache

# Using docker directly
docker build -f Dockerfile.cf-tool -t cf-tool:latest --no-cache .
```

## Notes

- The container runs mcp-chrome-bridge automatically on startup
- Your workspace files are mounted at `/workspace` in the container
- Port 12306 is exposed for Chrome extension communication
- All cf-tool commands should work once the Chrome extension is properly connected
