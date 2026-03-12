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

#import "CMPKeychain.h"
#import <TargetConditionals.h>

@import Security;

@implementation CMPKeychain

static NSMutableDictionary<NSString *, NSData *> *CMPKeychainFallbackStore;

+ (void)initialize {
    if (self == [CMPKeychain class]) {
        CMPKeychainFallbackStore = [NSMutableDictionary dictionary];
    }
}

+ (BOOL)isStatusOK:(OSStatus)status {
    return status == noErr;
}

+ (BOOL)isDeleteStatusOK:(OSStatus)status {
    return status == noErr || status == errSecItemNotFound;
}

+ (NSMutableDictionary *)queryForKey:(NSString *)key {
    return [@{(__bridge id)kSecClass : (__bridge id)kSecClassGenericPassword,
              (__bridge id)kSecAttrService : key,
              (__bridge id)kSecAttrAccount : key
              } mutableCopy];
}

+ (NSMutableDictionary *)addQueryForKey:(NSString *)key {
    NSMutableDictionary *query = [self queryForKey:key];
#if TARGET_OS_IOS || TARGET_OS_TV || TARGET_OS_WATCH
    [query setObject:(__bridge id)kSecAttrAccessibleAfterFirstUnlock forKey:(__bridge id)kSecAttrAccessible];
#endif
    return query;
}

+ (id)decodeObjectFromData:(NSData *)data {
    id object = nil;
    @try {
        if (@available(iOS 11.0, *)) {
            NSError *unarchiveError = nil;
            object = [NSKeyedUnarchiver unarchivedObjectOfClass:[NSObject class] fromData:data error:&unarchiveError];
            if (unarchiveError != nil || object == nil) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
                object = [NSKeyedUnarchiver unarchiveObjectWithData:data];
#pragma clang diagnostic pop
            }
        } else {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            object = [NSKeyedUnarchiver unarchiveObjectWithData:data];
#pragma clang diagnostic pop
        }
    }
    @catch (NSException *exception) {
        NSLog(@"Unarchiving failed with exception %@", exception.name);
        object = nil;
    }
    return object;
}

+ (BOOL)saveItem:(id)item forKey:(NSString *)key {
    NSMutableDictionary *keychainQuery = [self addQueryForKey:key];

    NSError *archivingError = nil;
    NSData *encodedItem = nil;
    if (@available(iOS 11.0, *)) {
        encodedItem = [NSKeyedArchiver archivedDataWithRootObject:item requiringSecureCoding:NO error:&archivingError];
    } else {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        encodedItem = [NSKeyedArchiver archivedDataWithRootObject:item];
#pragma clang diagnostic pop
    }

    if (encodedItem == nil || archivingError != nil) {
        return NO;
    }

    [keychainQuery setObject:encodedItem forKey:(__bridge id)kSecValueData];
    OSStatus addStatus = SecItemAdd((__bridge CFDictionaryRef)keychainQuery, NULL);
    if (addStatus == errSecDuplicateItem) {
        NSDictionary *attributesToUpdate = @{(__bridge id)kSecValueData : encodedItem};
        OSStatus updateStatus = SecItemUpdate((__bridge CFDictionaryRef)[self queryForKey:key], (__bridge CFDictionaryRef)attributesToUpdate);
        if ([self isStatusOK:updateStatus]) {
            return YES;
        }
    } else if ([self isStatusOK:addStatus]) {
        return YES;
    }

    @synchronized (CMPKeychainFallbackStore) {
        CMPKeychainFallbackStore[key] = encodedItem;
    }
    return YES;
}

+ (id)loadItemForKey:(NSString *)key {
    id object = nil;
    
    NSMutableDictionary *keychainQuery = [self queryForKey:key];
    
    [keychainQuery setObject:(__bridge id)kCFBooleanTrue forKey:(__bridge id)kSecReturnData];
    [keychainQuery setObject:(__bridge id)kSecMatchLimitOne forKey:(__bridge id)kSecMatchLimit];
    
    CFDataRef keyData = NULL;
    
    if ([self isStatusOK:SecItemCopyMatching((__bridge CFDictionaryRef)keychainQuery, (CFTypeRef *)&keyData)]) {
        object = [self decodeObjectFromData:(__bridge NSData *)keyData];
    }
    
    if (keyData) {
        CFRelease(keyData);
    }

    if (object == nil) {
        NSData *fallbackData = nil;
        @synchronized (CMPKeychainFallbackStore) {
            fallbackData = CMPKeychainFallbackStore[key];
        }
        if (fallbackData != nil) {
            object = [self decodeObjectFromData:fallbackData];
        }
    }
    
    return object;
}

+ (BOOL)deleteItemForKey:(NSString *)key {
    NSMutableDictionary *keychainQuery = [self queryForKey:key];
    BOOL keychainDeleted = [self isDeleteStatusOK:SecItemDelete((__bridge CFDictionaryRef)keychainQuery)];
    BOOL fallbackDeleted = NO;
    @synchronized (CMPKeychainFallbackStore) {
        if (CMPKeychainFallbackStore[key] != nil) {
            [CMPKeychainFallbackStore removeObjectForKey:key];
            fallbackDeleted = YES;
        }
    }
    return keychainDeleted || fallbackDeleted;
}

@end
