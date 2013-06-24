#ifndef WISP_WEBMAIL_CORE_SCREEN_CAPTURE_AUTHMAP_H
#define WISP_WEBMAIL_CORE_SCREEN_CAPTURE_AUTHMAP_H

#include <map>
#include <functional>

class AuthMap
{
    typedef std::function<void()> Auth;
protected:
    void GetAuth(int key,Auth auth){
        auth_map[key] = auth;
    }
    void UseAuth(int key){
        if (auth_map.find(key) != auth_map.end()){
            auth_map[key]();
        }
    }
private:
    std::map<int,Auth> auth_map;
};

#endif // WISP_WEBMAIL_CORE_SCREEN_CAPTURE_AUTHMAP_H