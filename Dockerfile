FROM alpine:latest

# Install build dependencies
RUN apk add --no-cache cmake make gcc g++ musl-dev

WORKDIR /app

# Copy source code and dependencies
COPY . .

# Install runtime dependencies
RUN apk add --no-cache libstdc++ readline readline-dev ncurses

# Build the project
RUN cmake -DCMAKE_BUILD_TYPE=Release -Bbuild -H. && make -C build

CMD ["/app/bin/processor"]
