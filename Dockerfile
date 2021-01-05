FROM alpine AS build

RUN apk --no-cache add cmake zlib-dev openssl-dev boost-dev alpine-sdk ninja

COPY . /workspace

WORKDIR /workspace

RUN git submodule update --init && git -C vendor/cpprestsdk submodule update --init

# Don't build and execute cpprestsdk tests and don't build cpprestsdk examples.
# Unfortunately it has to be done at this level.
RUN mkdir -p build && cd build && cmake -G Ninja -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release ../

RUN ninja -C build/

RUN ninja -C build/ test

RUN ninja -C build/ install

FROM alpine

COPY --from=build /usr/local /usr/local

RUN apk --no-cache update && apk --no-cache add boost

RUN ln -s /usr/local/lib64/*.so* /usr/local/lib/

ENTRYPOINT [ "server" ]
