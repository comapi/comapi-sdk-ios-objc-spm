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

import Foundation
import CommonCrypto

class JWTokenGenerator {

    struct AuthHeaders {
        static let HeaderType = "JWT"
    }

    static func generate(tokenFor nonce: String, profileId: String, issuer: String, audience: String, secret: String) -> String {
        let now = Date()
        let exp = Calendar.current.date(byAdding: .day, value: 30, to: now)!

        let header: [String: Any] = ["alg": "HS256", "typ": AuthHeaders.HeaderType]
        let claims: [String: Any] = [
            "nonce": nonce,
            "sub": profileId,
            "iss": issuer,
            "aud": audience,
            "iat": Int(now.timeIntervalSince1970),
            "exp": Int(exp.timeIntervalSince1970)
        ]

        let headerData = try! JSONSerialization.data(withJSONObject: header)
        let claimsData = try! JSONSerialization.data(withJSONObject: claims)

        let headerEncoded = base64URLEncode(headerData)
        let claimsEncoded = base64URLEncode(claimsData)
        let signingInput = "\(headerEncoded).\(claimsEncoded)"

        let signingData = signingInput.data(using: .utf8)!
        let secretData = secret.data(using: .utf8)!
        let signature = hmacSHA256(data: signingData, key: secretData)

        let token = "\(signingInput).\(signature)"
        print(token)
        return token
    }

    private static func base64URLEncode(_ data: Data) -> String {
        return data.base64EncodedString()
            .replacingOccurrences(of: "+", with: "-")
            .replacingOccurrences(of: "/", with: "_")
            .replacingOccurrences(of: "=", with: "")
    }

    private static func hmacSHA256(data: Data, key: Data) -> String {
        var digest = [UInt8](repeating: 0, count: Int(CC_SHA256_DIGEST_LENGTH))
        data.withUnsafeBytes { dataBytes in
            key.withUnsafeBytes { keyBytes in
                CCHmac(CCHmacAlgorithm(kCCHmacAlgSHA256),
                       keyBytes.baseAddress, key.count,
                       dataBytes.baseAddress, data.count,
                       &digest)
            }
        }
        return base64URLEncode(Data(digest))
    }
}
