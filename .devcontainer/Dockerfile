ARG VARIANT="jammy"
FROM ubuntu:${VARIANT}

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -qq

# Install necessary packages available from standard repos
RUN apt-get install -y --no-install-recommends \
        bash-completion ca-certificates curl sudo unzip zip

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Install devel packages
RUN apt-get install -y --no-install-recommends \
        ccache cmake cmake-curses-gui cmake-extras \
        cppcheck git make ninja-build valgrind \
        python3 python3-pip

# Install cmake-format
RUN python3 -m pip install --upgrade pip setuptools && \
    python3 -m pip install cmakelang

# Install gcc
RUN apt-get install -y --no-install-recommends \
        gcc gcc-arm-none-eabi g++ gdb \
        libstdc++-arm-none-eabi-newlib

ARG LLVM_VER="14"
# Install clang ${LLVM_VER}
RUN apt-get install -y --no-install-recommends \
        clang clangd clang-tidy lld lldb llvm-dev libclang-dev

# Install C++ test framework
RUN apt-get install -y --no-install-recommends \
        libgtest-dev libgmock-dev

## Cleanup cached apt data we don't need anymore
RUN apt-get autoremove -y && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install include-what-you-use
ENV IWYU /usr/src/iwyu
ENV IWYU_BUILD ${IWYU}/build
ENV IWYU_SRC ${IWYU}/include-what-you-use
RUN mkdir -p ${IWYU_BUILD} && \
    git clone --branch clang_${LLVM_VER} \
        https://github.com/include-what-you-use/include-what-you-use.git \
        ${IWYU_SRC}
RUN CC=clang-${LLVM_VER} CXX=clang++-${LLVM_VER} cmake -S ${IWYU_SRC} \
        -B ${IWYU_BUILD} \
        -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${LLVM_VER} && \
    cmake --build ${IWYU_BUILD} -j && \
    cmake --install ${IWYU_BUILD}

# Per https://github.com/include-what-you-use/include-what-you-use#how-to-install:
# `You need to copy the Clang include directory to the expected location before
#  running (similarly, use include-what-you-use -print-resource-dir to learn
#  exactly where IWYU wants the headers).`
RUN mkdir -p $(include-what-you-use -print-resource-dir 2>/dev/null)
RUN ln -s $(readlink -f /usr/lib/clang/${LLVM_VER}/include) \
    $(include-what-you-use -print-resource-dir 2>/dev/null)/include

# Clone project_options
ENV PROJECT_OPTIONS_SRC /usr/src/project_options
RUN git clone --branch v0.29.0 \
        https://github.com/aminya/project_options.git \
        ${PROJECT_OPTIONS_SRC}

# Clone STM32CubeF1
ENV STM32_CUBE_F1_SRC /usr/src/STM32CubeF1
RUN git clone --branch master \
        https://github.com/STMicroelectronics/STM32CubeF1.git \
        ${STM32_CUBE_F1_SRC}

# Clone stm32-cmake
ENV STM32_CMAKE_SRC /usr/src/stm32-cmake
RUN git clone --branch master \
        https://github.com/ObKo/stm32-cmake.git \
        ${STM32_CMAKE_SRC}