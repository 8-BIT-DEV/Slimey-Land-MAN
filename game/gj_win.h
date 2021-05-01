/*
    (c) 2021 8_BIT-DEV Under MIT License
    (c) modifyed for Slimey Land MAN! to turn off gj api features on WIN32 builds
    p_ : meaning private function though theres nothing stopping you from using p_ functions
    _e : for enums
    _u : for unions
    _t : for structs
*/

#ifndef WIN32
#error GNU/LINUX BUILDS ARE NOT ALLOWED GJ API WIN
#endif // WIN32

#ifdef GJAPI_H
#error ALREADY HAVE gj.h included!
#endif // GJAPI_H

#ifndef GJAPI_H
#define GJAPI_H

#define set_id(id);
#define set_pkey(pkey);

// General functions
#define gj_api();
#define gj_login(username, token);

// trophies
#define gj_give_trophie(tid);
#define gj_revoke_trophie(tid);

// scores
#define gj_add_score(tid, score);
#define gj_add_guest_score(name, tid, score);
// shouldnt need to implement more of the score functions
// theses should do

// sessions
#define gj_open_session();
#define gj_close_session();
#define gj_ping_session();
#define gj_check_session(); // not implemented yet

// data
// pass everything as a po#defineer to the set data function
#define gj_set_data(k, type, ...);
#define gj_remove_data(k);
#define gj_get_data(k);
// i'll implement these later

// time
#define gj_get_time();
// i'll implement this later

// private functions
/* uneeded if gj api is turned off
char* p_gethash(char* in);
char* p_makeurl(char* endpo#define, #define argcount, ...);
#define p_checkgood(http_get_response_t* got);
*/

#endif // GJAPI_H

