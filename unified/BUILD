cc_library(
    name = "api_header",
    hdrs = ["api.h"],
)

cc_library(
    name = "static_lib",
    srcs = ["dso.cc"],
    hdrs = ["api.h"],
)

cc_binary(
    name = "static_bin",
    srcs = ["user.cc"],
    deps = [
        ":static_lib",
    ],
)


# Dynamicly linked counterpart
cc_binary(
    name = "libdso.so",
    linkshared = 1,
    deps = [
        ":static_lib",
    ],
)

cc_binary(
    name = "dynamic_bin",
    srcs = [
        "user.cc",
        ":libdso.so",
    ],
    deps = [
        ":api_header",
    ],
)
