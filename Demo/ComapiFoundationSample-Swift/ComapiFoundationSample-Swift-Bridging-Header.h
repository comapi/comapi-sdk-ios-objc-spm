//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

#if __has_include(<SocketRocket/SocketRocket.h>)
#import <SocketRocket/SocketRocket.h>
#elif __has_include(<SocketRocket.h>)
#import <SocketRocket.h>
#else
@import SocketRocket;
#endif
#if __has_include(<CMPComapiFoundation/CMPComapiFoundation.h>)
#import <CMPComapiFoundation/CMPComapiFoundation.h>
#elif __has_include(<CMPComapiFoundation.h>)
#import <CMPComapiFoundation.h>
#else
@import CMPComapiFoundation;
#endif

