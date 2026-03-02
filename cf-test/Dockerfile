FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Download cf-tool (the version your workflow uses)
RUN wget https://github.com/Komosa/cf_binaries/raw/master/cf_linux_amd64 -O /usr/local/bin/cf && \
    chmod +x /usr/local/bin/cf

# Create config directory
RUN mkdir -p /root/.config/cf

WORKDIR /workspace

# Entry point for testing
CMD ["/bin/bash"]


