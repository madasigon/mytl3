FROM gitpod/workspace-full
                    
USER gitpod

# Install custom tools, runtime, etc. using apt-get
# For example, the command below would install "bastet" - a command line tetris clone:
#
# RUN sudo apt-get -q update && #     sudo apt-get install -yq bastet && #     sudo rm -rf /var/lib/apt/lists/*
#
# More information: https://www.gitpod.io/docs/config-docker/
 RUN ls /
 RUN sudo apt update \
  && sudo apt -y install firefox
 RUN wget https://github.com/mozilla/geckodriver/releases/download/v0.26.0/geckodriver-v0.26.0-linux64.tar.gz \
  && tar -zxvf geckodriver-v0.26.0-linux64.tar.gz \
  && mkdir bin \
  && mv geckodriver bin/geckodriver \
  && export PATH="/home/gitpod/bin:$PATH"

