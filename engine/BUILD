cc_binary(
    name = "basic_engine_runner",
    srcs = ["hello-world.cpp", "engine.hpp", "basic_evaluator.hpp"],
    # hdrs = ["hello-greet.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//engine/board_v1.0/general:chess-basic",
        "//engine/board_v1.0:basic_board",
    ],
)