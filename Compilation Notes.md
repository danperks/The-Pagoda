# Compilation Notes

## Libraries

To include libraries, install them with vcpkg and make sure to add `-L [vcpkg include folder] to the end of your g++ command.

### Individual library locations

- Perks - 'D:\Programs\VCPKG\installed\x86-windows\include'
- Chalmers - Using Visual Studio
- Harrison - To Be Filled
- Robbie - To Be Filled
- Zaber - To Be Filled

## Other Notes

At the moment, the server and client need to be compiled with `-lws2_32 -std=c++0x` to get them to compile correctly.
