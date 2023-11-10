from http import cookies
import os

# # Create a new cookie
# new_cookie = cookies.SimpleCookie()
# new_cookie['username'] = 'johndoe'

# # Set the cookie in the response headers
# print('Content-Type: text/html')
# print(new_cookie.output())

# Retrieve the cookie from the request headers
cookie_string = os.environ.get('HTTP_COOKIE')
if cookie_string:
    received_cookie = cookies.SimpleCookie()
    received_cookie.load(cookie_string)
    username = received_cookie.get('username').value
    print "hello, again"
else:
    print('Welcome, new user!')