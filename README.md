# dotdigital push and app messaging iOS SDK 

Client to connect your iOS application with [dotdigital's Engagement Cloud](http://dotdigital.com/) and CPaaS APIs for push and in-app messgaing.


This repo distributes the [CMPComapiFoundation](https://github.com/comapi/comapi-sdk-ios-objc) library via Swift Package Manager.

Note: this version of the library requires setting "development" or "production" in the CMPComapiConfig passed to the SDK initialization method.
~~~swift
        ComapiConfig().setApnsEnvironment("development")
~~~

For more information about the integration please visit [the website](http://docs.comapi.com/reference#one-sdk-ios).
