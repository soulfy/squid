/*
 * auth_ntlm.h
 * Internal declarations for the ntlm auth module
 */

#ifndef __AUTH_NTLM_H__
#define __AUTH_NTLM_H__
#include "auth/Gadgets.h"
#include "auth/User.h"
#include "auth/UserRequest.h"
#include "auth/Config.h"
#include "helper.h"

#define DefaultAuthenticateChildrenMax  32	/* 32 processes */

#ifndef __AUTH_AUTHENTICATE_STATE_T__
#define __AUTH_AUTHENTICATE_STATE_T__
typedef enum {
    AUTHENTICATE_STATE_NONE,
    AUTHENTICATE_STATE_INITIAL,
    AUTHENTICATE_STATE_IN_PROGRESS,
    AUTHENTICATE_STATE_DONE,
    AUTHENTICATE_STATE_FAILED
} auth_state_t;                 /* connection level auth state */

/* Generic */

typedef struct {
    void *data;
    AuthUserRequest *auth_user_request;
    RH *handler;
} authenticateStateData;
#endif

class NTLMUser : public AuthUser
{

public:
    MEMPROXY_CLASS(NTLMUser);
    virtual void deleteSelf() const;
    NTLMUser(AuthConfig *);
    ~NTLMUser();
    dlink_list proxy_auth_list;
};

MEMPROXY_CLASS_INLINE(NTLMUser);

typedef class NTLMUser ntlm_user_t;

class AuthNTLMUserRequest : public AuthUserRequest
{

public:
    MEMPROXY_CLASS(AuthNTLMUserRequest);

    AuthNTLMUserRequest();
    virtual ~AuthNTLMUserRequest();
    virtual int authenticated() const;
    virtual void authenticate(HttpRequest * request, ConnStateData * conn, http_hdr_type type);
    virtual int module_direction();
    virtual void onConnectionClose(ConnStateData *);
    virtual void module_start(RH *, void *);

    virtual const char * connLastHeader();

    /* we need to store the helper server between requests */
    helper_stateful_server *authserver;
    void releaseAuthServer(void); ///< Release authserver NTLM helpers properly when finished or abandoning.

    /* what connection is this associated with */
//    ConnStateData * conn;

    /* how far through the authentication process are we? */
    auth_state_t auth_state;

    /* our current blob to pass to the client */
    char *server_blob;
    /* our current blob to pass to the server */
    char *client_blob;

    /* currently waiting for helper response */
    unsigned char waiting;

    /* need access to the request flags to mess around on pconn failure */
    HttpRequest *request;
};

MEMPROXY_CLASS_INLINE(AuthNTLMUserRequest);

/* configuration runtime data */

class AuthNTLMConfig : public AuthConfig
{

public:
    AuthNTLMConfig();
    virtual bool active() const;
    virtual bool configured() const;
    virtual AuthUserRequest *decode(char const *proxy_auth);
    virtual void done();
    virtual void dump(StoreEntry *, const char *, AuthConfig *);
    virtual void fixHeader(AuthUserRequest *, HttpReply *, http_hdr_type, HttpRequest *);
    virtual void init(AuthConfig *);
    virtual void parse(AuthConfig *, int, char *);
    virtual void registerWithCacheManager(void);
    virtual const char * type() const;
    int authenticateChildren;
    int keep_alive;
    wordlist *authenticate;
};

typedef class AuthNTLMConfig auth_ntlm_config;

#endif
