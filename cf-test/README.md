# Testing lcian/codeforces-cli

This is a maintained fork of cf-tool that fixes:
- Broken HTML parsing
- Cloudflare captcha issues
- Input/output parsing

**Note:** The cf-darwin-amd64 file in the parent directory is for macOS.
The Dockerfile downloads the Linux version automatically.

## Build the Docker image:

```bash
docker build -t cf-lcian -f Dockerfile.lcian .
```

## Enter interactive shell:

```bash
docker run -it --rm cf-lcian
```

## Once inside the container, test the tool:

```bash
# Check version/help
cf

# Login to Codeforces
cf login hellohellohellohello

# Then enter password when prompted: #A9*tMPdWvkdwk4tP7Lc
```

## Test with mounted workspace:

```bash
docker run -it --rm -v ${PWD}:/workspace cf-lcian
```

On Windows PowerShell, use:
```powershell
docker run -it --rm -v ${PWD}:/workspace cf-lcian
```

