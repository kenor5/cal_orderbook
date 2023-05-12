FROM codenvy/cpp_gcc
RUN mkdir /home/user/app; mkdir /home/user/app/include; mkdir /home/user/app/bin; mkdir /home/user/app/src
ADD include/* /home/user/app/include/
ADD src/*.cpp /home/user/app/src/
ADD Makefile /home/user/app/
WORKDIR /home/user/app
RUN make all
