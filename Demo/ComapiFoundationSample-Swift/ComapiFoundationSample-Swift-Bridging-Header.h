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
#if __has_include(<Base64/MF_Base64Additions.h>)
#import <Base64/MF_Base64Additions.h>
#elif __has_include(<MF_Base64Additions.h>)
#import <MF_Base64Additions.h>
#else
@import Base64;
#endif

#if __has_include(<JWT/JWT.h>)
#import <JWT/JWT.h>
#elif __has_include(<JWT.h>)
#import <JWT.h>
#else
@import JWT;
#endif
