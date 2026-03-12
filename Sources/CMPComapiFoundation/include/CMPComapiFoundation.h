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

#if SWIFT_PACKAGE || !__has_include(<CMPComapiFoundation/CMPHTTPHeader.h>)
#import "CMPHTTPHeader.h"
#import "CMPStateDelegate.h"
#import "CMPComapi.h"
#import "CMPComapiClient.h"
#import "CMPAPIConfiguration.h"
#import "CMPComapiConfig.h"
#import "CMPLogConfig.h"
#import "CMPConstants.h"
#import "CMPErrors.h"
#import "CMPLog.h"
#import "CMPLogger.h"
#import "CMPLogLevel.h"
#import "CMPFileDestination.h"
#import "CMPLoggingDestination.h"
#import "CMPXcodeConsoleDestination.h"
#import "CMPAuthenticationDelegate.h"
#import "CMPJSONConstructable.h"
#import "CMPJSONDecoding.h"
#import "CMPJSONEncoding.h"
#import "CMPJSONRepresentable.h"
#import "CMPRequestManager.h"
#import "CMPRequestPerformer.h"
#import "CMPRequestPerforming.h"
#import "CMPBaseService.h"
#import "CMPServices.h"
#import "CMPMessagingService.h"
#import "CMPProfileService.h"
#import "CMPSessionService.h"
#import "CMPAuthChallengeHandler.h"
#import "CMPSessionAuthProvider.h"
#import "CMPSessionDelegate.h"
#import "CMPSessionManager.h"
#import "CMPEventDelegate.h"
#import "CMPEventParser.h"
#import "CMPEvent.h"
#import "CMPConversationEvents.h"
#import "CMPConversationMessageEvents.h"
#import "CMPProfileEvents.h"
#import "CMPSocketEvents.h"
#import "CMPAddConversationTemplate.h"
#import "CMPAddParticipantsTemplate.h"
#import "CMPContentUploadTemplate.h"
#import "CMPDeleteConversationTemplate.h"
#import "CMPEventQueryTemplate.h"
#import "CMPGetConversationsTemplate.h"
#import "CMPGetConversationTemplate.h"
#import "CMPGetMessagesTemplate.h"
#import "CMPGetParticipantsTemplate.h"
#import "CMPParticipantTypingOffTemplate.h"
#import "CMPParticipantTypingTemplate.h"
#import "CMPPendingOperation.h"
#import "CMPRemoveParticipantsTemplate.h"
#import "CMPSendMessagesTemplate.h"
#import "CMPSendStatusUpdateTemplate.h"
#import "CMPUpdateConversationTemplate.h"
#import "CMPContentData.h"
#import "CMPContentUploadResult.h"
#import "CMPConversation.h"
#import "CMPConversationParticipant.h"
#import "CMPConversationScope.h"
#import "CMPConversationUpdate.h"
#import "CMPGetMessagesResult.h"
#import "CMPMessage.h"
#import "CMPMessageAlert.h"
#import "CMPMessageAlertPlatforms.h"
#import "CMPMessageContext.h"
#import "CMPMessageDeliveryStatus.h"
#import "CMPMessagePart.h"
#import "CMPMessageParticipant.h"
#import "CMPMessageStatus.h"
#import "CMPMessageStatusUpdate.h"
#import "CMPNewConversation.h"
#import "CMPOrphanedEvent.h"
#import "CMPRole.h"
#import "CMPRoleAttributes.h"
#import "CMPRoles.h"
#import "CMPSendableMessage.h"
#import "CMPSendMessagesResult.h"
#import "CMPGetProfileTemplate.h"
#import "CMPPatchProfileTemplate.h"
#import "CMPQueryProfilesTemplate.h"
#import "CMPUpdateProfileTemplate.h"
#import "CMPProfile.h"
#import "CMPQueryBuilder.h"
#import "CMPSetAPNSDetailsTemplate.h"
#import "CMPAPNSDetails.h"
#import "CMPAPNSDetailsBody.h"
#import "CMPHTTPRequestTemplate.h"
#import "CMPRequestTemplate.h"
#import "CMPResult.h"
#import "CMPAuthorizeSessionTemplate.h"
#import "CMPDeleteSessionTemplate.h"
#import "CMPStartNewSessionTemplate.h"
#import "CMPAuthenticationChallenge.h"
#import "CMPAuthorizeSessionBody.h"
#import "CMPSession.h"
#import "CMPSessionAuth.h"
#import "CMPSocketTemplate.h"
#import "CMPURLResult.h"
#import "CMPBroadcastDelegate.h"
#import "CMPSocketDelegate.h"
#import "CMPSocketManager.h"
#import "CMPTokenState.h"
#import "CMPKeychain.h"
#import "NSData+CMPUtility.h"
#import "NSDate+CMPUtility.h"
#import "NSDateFormatter+CMPUtility.h"
#import "NSString+CMPUtility.h"
#import "NSURLRequest+CMPUtility.h"
#import "NSURLResponse+CMPUtility.h"
#else
#import <CMPComapiFoundation/CMPHTTPHeader.h>
#import <CMPComapiFoundation/CMPStateDelegate.h>
#import <CMPComapiFoundation/CMPComapi.h>
#import <CMPComapiFoundation/CMPComapiClient.h>
#import <CMPComapiFoundation/CMPAPIConfiguration.h>
#import <CMPComapiFoundation/CMPComapiConfig.h>
#import <CMPComapiFoundation/CMPLogConfig.h>
#import <CMPComapiFoundation/CMPConstants.h>
#import <CMPComapiFoundation/CMPErrors.h>
#import <CMPComapiFoundation/CMPLog.h>
#import <CMPComapiFoundation/CMPLogger.h>
#import <CMPComapiFoundation/CMPLogLevel.h>
#import <CMPComapiFoundation/CMPFileDestination.h>
#import <CMPComapiFoundation/CMPLoggingDestination.h>
#import <CMPComapiFoundation/CMPXcodeConsoleDestination.h>
#import <CMPComapiFoundation/CMPAuthenticationDelegate.h>
#import <CMPComapiFoundation/CMPJSONConstructable.h>
#import <CMPComapiFoundation/CMPJSONDecoding.h>
#import <CMPComapiFoundation/CMPJSONEncoding.h>
#import <CMPComapiFoundation/CMPJSONRepresentable.h>
#import <CMPComapiFoundation/CMPRequestManager.h>
#import <CMPComapiFoundation/CMPRequestPerformer.h>
#import <CMPComapiFoundation/CMPRequestPerforming.h>
#import <CMPComapiFoundation/CMPBaseService.h>
#import <CMPComapiFoundation/CMPServices.h>
#import <CMPComapiFoundation/CMPMessagingService.h>
#import <CMPComapiFoundation/CMPProfileService.h>
#import <CMPComapiFoundation/CMPSessionService.h>
#import <CMPComapiFoundation/CMPAuthChallengeHandler.h>
#import <CMPComapiFoundation/CMPSessionAuthProvider.h>
#import <CMPComapiFoundation/CMPSessionDelegate.h>
#import <CMPComapiFoundation/CMPSessionManager.h>
#import <CMPComapiFoundation/CMPEventDelegate.h>
#import <CMPComapiFoundation/CMPEventParser.h>
#import <CMPComapiFoundation/CMPEvent.h>
#import <CMPComapiFoundation/CMPConversationEvents.h>
#import <CMPComapiFoundation/CMPConversationMessageEvents.h>
#import <CMPComapiFoundation/CMPProfileEvents.h>
#import <CMPComapiFoundation/CMPSocketEvents.h>
#import <CMPComapiFoundation/CMPAddConversationTemplate.h>
#import <CMPComapiFoundation/CMPAddParticipantsTemplate.h>
#import <CMPComapiFoundation/CMPContentUploadTemplate.h>
#import <CMPComapiFoundation/CMPDeleteConversationTemplate.h>
#import <CMPComapiFoundation/CMPEventQueryTemplate.h>
#import <CMPComapiFoundation/CMPGetConversationsTemplate.h>
#import <CMPComapiFoundation/CMPGetConversationTemplate.h>
#import <CMPComapiFoundation/CMPGetMessagesTemplate.h>
#import <CMPComapiFoundation/CMPGetParticipantsTemplate.h>
#import <CMPComapiFoundation/CMPParticipantTypingOffTemplate.h>
#import <CMPComapiFoundation/CMPParticipantTypingTemplate.h>
#import <CMPComapiFoundation/CMPPendingOperation.h>
#import <CMPComapiFoundation/CMPRemoveParticipantsTemplate.h>
#import <CMPComapiFoundation/CMPSendMessagesTemplate.h>
#import <CMPComapiFoundation/CMPSendStatusUpdateTemplate.h>
#import <CMPComapiFoundation/CMPUpdateConversationTemplate.h>
#import <CMPComapiFoundation/CMPContentData.h>
#import <CMPComapiFoundation/CMPContentUploadResult.h>
#import <CMPComapiFoundation/CMPConversation.h>
#import <CMPComapiFoundation/CMPConversationParticipant.h>
#import <CMPComapiFoundation/CMPConversationScope.h>
#import <CMPComapiFoundation/CMPConversationUpdate.h>
#import <CMPComapiFoundation/CMPGetMessagesResult.h>
#import <CMPComapiFoundation/CMPMessage.h>
#import <CMPComapiFoundation/CMPMessageAlert.h>
#import <CMPComapiFoundation/CMPMessageAlertPlatforms.h>
#import <CMPComapiFoundation/CMPMessageContext.h>
#import <CMPComapiFoundation/CMPMessageDeliveryStatus.h>
#import <CMPComapiFoundation/CMPMessagePart.h>
#import <CMPComapiFoundation/CMPMessageParticipant.h>
#import <CMPComapiFoundation/CMPMessageStatus.h>
#import <CMPComapiFoundation/CMPMessageStatusUpdate.h>
#import <CMPComapiFoundation/CMPNewConversation.h>
#import <CMPComapiFoundation/CMPOrphanedEvent.h>
#import <CMPComapiFoundation/CMPRole.h>
#import <CMPComapiFoundation/CMPRoleAttributes.h>
#import <CMPComapiFoundation/CMPRoles.h>
#import <CMPComapiFoundation/CMPSendableMessage.h>
#import <CMPComapiFoundation/CMPSendMessagesResult.h>
#import <CMPComapiFoundation/CMPGetProfileTemplate.h>
#import <CMPComapiFoundation/CMPPatchProfileTemplate.h>
#import <CMPComapiFoundation/CMPQueryProfilesTemplate.h>
#import <CMPComapiFoundation/CMPUpdateProfileTemplate.h>
#import <CMPComapiFoundation/CMPProfile.h>
#import <CMPComapiFoundation/CMPQueryBuilder.h>
#import <CMPComapiFoundation/CMPSetAPNSDetailsTemplate.h>
#import <CMPComapiFoundation/CMPAPNSDetails.h>
#import <CMPComapiFoundation/CMPAPNSDetailsBody.h>
#import <CMPComapiFoundation/CMPHTTPRequestTemplate.h>
#import <CMPComapiFoundation/CMPRequestTemplate.h>
#import <CMPComapiFoundation/CMPResult.h>
#import <CMPComapiFoundation/CMPAuthorizeSessionTemplate.h>
#import <CMPComapiFoundation/CMPDeleteSessionTemplate.h>
#import <CMPComapiFoundation/CMPStartNewSessionTemplate.h>
#import <CMPComapiFoundation/CMPAuthenticationChallenge.h>
#import <CMPComapiFoundation/CMPAuthorizeSessionBody.h>
#import <CMPComapiFoundation/CMPSession.h>
#import <CMPComapiFoundation/CMPSessionAuth.h>
#import <CMPComapiFoundation/CMPSocketTemplate.h>
#import <CMPComapiFoundation/CMPURLResult.h>
#import <CMPComapiFoundation/CMPBroadcastDelegate.h>
#import <CMPComapiFoundation/CMPSocketDelegate.h>
#import <CMPComapiFoundation/CMPSocketManager.h>
#import <CMPComapiFoundation/CMPTokenState.h>
#import <CMPComapiFoundation/CMPKeychain.h>
#import <CMPComapiFoundation/NSData+CMPUtility.h>
#import <CMPComapiFoundation/NSDate+CMPUtility.h>
#import <CMPComapiFoundation/NSDateFormatter+CMPUtility.h>
#import <CMPComapiFoundation/NSString+CMPUtility.h>
#import <CMPComapiFoundation/NSURLRequest+CMPUtility.h>
#import <CMPComapiFoundation/NSURLResponse+CMPUtility.h>
#endif







