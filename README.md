# Dotdigital push and app messaging iOS SDK 

Client to connect your iOS application with [Dotdigital's](http://dotdigital.com/) platform and [Enterprise Communications API](https://docs.cpaas.dotdigital.com/) for push and in-app messaging.


This repo distributes the [CMPComapiFoundation](https://github.com/comapi/comapi-sdk-ios-objc) library via Swift Package Manager.

_Note: this version of the library requires setting "development" or "production" in the CMPComapiConfig passed to the SDK initialization method._

~~~swift
        ComapiConfig().setApnsEnvironment("development")
~~~

For more information about the using the library, please visit:
* [Using Push or App Messaging with Dotdigital Enterprise Comms API](https://docs.cpaas.dotdigital.com/reference/one-sdk-ios)
* [Using Push or App Messaging with the Dotdigital platform](https://developer.dotdigital.com/docs/setting-up-push-notifications)
