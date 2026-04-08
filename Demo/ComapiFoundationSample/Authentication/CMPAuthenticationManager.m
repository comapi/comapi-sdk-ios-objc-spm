//
// The MIT License (MIT)
// Copyright (c) 2017 Comapi (trading name of Dynmark International Limited)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
// to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#import "CMPAuthenticationManager.h"
#import <CommonCrypto/CommonHMAC.h>

static NSString *base64URLEncode(NSData *data) {
    NSString *base64 = [data base64EncodedStringWithOptions:0];
    base64 = [base64 stringByReplacingOccurrencesOfString:@"+" withString:@"-"];
    base64 = [base64 stringByReplacingOccurrencesOfString:@"/" withString:@"_"];
    base64 = [base64 stringByReplacingOccurrencesOfString:@"=" withString:@""];
    return base64;
}

@implementation CMPAuthenticationManager

+ (NSString *)generateTokenForNonce:(NSString *)nonce profileID:(NSString *)profileID issuer:(NSString *)issuer audience:(NSString *)audience secret:(NSString *)secret {
    NSDate *now = [NSDate date];
    NSDate *exp = [NSCalendar.currentCalendar dateByAddingUnit:NSCalendarUnitDay value:30 toDate:now options:0];

    NSDictionary *header = @{@"alg": @"HS256", @"typ": @"JWT"};
    NSDictionary *payload = @{@"nonce": nonce,
                               @"sub": profileID,
                               @"iss": issuer,
                               @"aud": audience,
                               @"iat": @((long long)now.timeIntervalSince1970),
                               @"exp": @((long long)exp.timeIntervalSince1970)};

    NSData *headerData = [NSJSONSerialization dataWithJSONObject:header options:0 error:nil];
    NSData *payloadData = [NSJSONSerialization dataWithJSONObject:payload options:0 error:nil];

    NSString *headerEncoded = base64URLEncode(headerData);
    NSString *payloadEncoded = base64URLEncode(payloadData);
    NSString *signingInput = [NSString stringWithFormat:@"%@.%@", headerEncoded, payloadEncoded];

    NSData *signingData = [signingInput dataUsingEncoding:NSUTF8StringEncoding];
    NSData *secretData = [secret dataUsingEncoding:NSUTF8StringEncoding];

    uint8_t digest[CC_SHA256_DIGEST_LENGTH];
    CCHmac(kCCHmacAlgSHA256,
           secretData.bytes, secretData.length,
           signingData.bytes, signingData.length,
           digest);
    NSData *signatureData = [NSData dataWithBytes:digest length:CC_SHA256_DIGEST_LENGTH];
    NSString *signature = base64URLEncode(signatureData);

    return [NSString stringWithFormat:@"%@.%@", signingInput, signature];
}

@end
