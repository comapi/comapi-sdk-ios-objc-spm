// swift-tools-version: 5.6

import PackageDescription

let package = Package(
    name: "CMPComapiFoundation",
    platforms: [.iOS(.v10)],
    products: [
        .library(
            name: "CMPComapiFoundation",
            targets: ["CMPComapiFoundation"]),
    ],
    dependencies: [
        .package(url: "https://github.com/flashphoner/SocketRocketSPM.git", from: "1.0.2")    ],
    targets: [
        .target(
            name: "CMPComapiFoundation",
            dependencies: [
                .product(name: "SocketRocket", package: "SocketRocketSPM")
            ],
            resources: [
                .process("PrivacyInfo.xcprivacy")
            ]),
        .testTarget(
            name: "CMPComapiFoundationTests",
            dependencies: ["CMPComapiFoundation"],
            cSettings: [
                .headerSearchPath("./"),
                .headerSearchPath("Categories"),
                .headerSearchPath("JSON"),
                .headerSearchPath("Mocks")
            ]),
    ]
)
