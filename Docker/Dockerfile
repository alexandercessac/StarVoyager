FROM alpine as build
WORKDIR /
# Install build dependencies
RUN apk update\
 && apk add --no-cache musl-dev ncurses-dev ncurses-terminfo git make gcc\
 && rm -rf /var/cache/apk/* /tmp/*

# Pull source
RUN mkdir /src\
 && cd /src\
 && git clone https://github.com/alexandercessac/StarVoyager.git

# Build application
RUN cd /src/StarVoyager\
 && make\
 && chmod +x /src/StarVoyager/StarVoyager

# Copy application to final image
FROM alpine as final
WORKDIR /
COPY --from=build /src/StarVoyager/ /app

# Install run dependencies
RUN apk update\
 && apk add --no-cache ncurses-libs ncurses-terminfo-base ncurses-static\
 && rm -rf /var/cache/apk/* /tmp/*

ENTRYPOINT ["/app/StarVoyager"]
