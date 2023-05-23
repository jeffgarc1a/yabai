#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#define EVENT_QUEUED    0x0
#define EVENT_PROCESSED 0x1

#define EVENT_SUCCESS 0x0
#define EVENT_FAILURE 0x1

#define event_status(e) ((e)  & 0x1)
#define event_result(e) ((e) >> 0x1)

#define EVENT_HANDLER(event_type) uint32_t EVENT_HANDLER_##event_type(void *context, int param1)

#define EVENT_TYPE_LIST \
    EVENT_TYPE_ENTRY(APPLICATION_LAUNCHED) \
    EVENT_TYPE_ENTRY(APPLICATION_TERMINATED) \
    EVENT_TYPE_ENTRY(APPLICATION_FRONT_SWITCHED) \
    EVENT_TYPE_ENTRY(APPLICATION_ACTIVATED) \
    EVENT_TYPE_ENTRY(APPLICATION_DEACTIVATED) \
    EVENT_TYPE_ENTRY(APPLICATION_VISIBLE) \
    EVENT_TYPE_ENTRY(APPLICATION_HIDDEN) \
    EVENT_TYPE_ENTRY(WINDOW_CREATED) \
    EVENT_TYPE_ENTRY(WINDOW_DESTROYED) \
    EVENT_TYPE_ENTRY(WINDOW_FOCUSED) \
    EVENT_TYPE_ENTRY(WINDOW_MOVED) \
    EVENT_TYPE_ENTRY(WINDOW_RESIZED) \
    EVENT_TYPE_ENTRY(WINDOW_MINIMIZED) \
    EVENT_TYPE_ENTRY(WINDOW_DEMINIMIZED) \
    EVENT_TYPE_ENTRY(WINDOW_TITLE_CHANGED) \
    EVENT_TYPE_ENTRY(SLS_WINDOW_MOVED) \
    EVENT_TYPE_ENTRY(SLS_WINDOW_RESIZED) \
    EVENT_TYPE_ENTRY(SLS_WINDOW_ORDER_CHANGED) \
    EVENT_TYPE_ENTRY(SLS_WINDOW_IS_VISIBLE) \
    EVENT_TYPE_ENTRY(SLS_WINDOW_IS_INVISIBLE) \
    EVENT_TYPE_ENTRY(SPACE_CHANGED) \
    EVENT_TYPE_ENTRY(DISPLAY_ADDED) \
    EVENT_TYPE_ENTRY(DISPLAY_REMOVED) \
    EVENT_TYPE_ENTRY(DISPLAY_MOVED) \
    EVENT_TYPE_ENTRY(DISPLAY_RESIZED) \
    EVENT_TYPE_ENTRY(DISPLAY_CHANGED) \
    EVENT_TYPE_ENTRY(MOUSE_DOWN) \
    EVENT_TYPE_ENTRY(MOUSE_UP) \
    EVENT_TYPE_ENTRY(MOUSE_DRAGGED) \
    EVENT_TYPE_ENTRY(MOUSE_MOVED) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_SHOW_ALL_WINDOWS) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_SHOW_FRONT_WINDOWS) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_SHOW_DESKTOP) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_ENTER) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_CHECK_FOR_EXIT) \
    EVENT_TYPE_ENTRY(MISSION_CONTROL_EXIT) \
    EVENT_TYPE_ENTRY(DOCK_DID_RESTART) \
    EVENT_TYPE_ENTRY(MENU_OPENED) \
    EVENT_TYPE_ENTRY(MENU_CLOSED) \
    EVENT_TYPE_ENTRY(MENU_BAR_HIDDEN_CHANGED) \
    EVENT_TYPE_ENTRY(DOCK_DID_CHANGE_PREF) \
    EVENT_TYPE_ENTRY(SYSTEM_WOKE) \
    EVENT_TYPE_ENTRY(DAEMON_MESSAGE)

enum event_type
{
#define EVENT_TYPE_ENTRY(value) value,
    EVENT_TYPE_LIST
#undef EVENT_TYPE_ENTRY
};

struct event
{
    void *context;
    volatile uint32_t *info;
    enum event_type type;
    int param1;
};

struct event_loop_item
{
    struct event_loop_item *next;
    struct event event;
};

struct event_loop
{
    bool is_running;
    pthread_t thread;
    sem_t *semaphore;
    struct memory_pool pool;
    struct event_loop_item *head;
    struct event_loop_item *tail;
};

bool event_loop_init(struct event_loop *event_loop);
bool event_loop_begin(struct event_loop *event_loop);
bool event_loop_end(struct event_loop *event_loop);
void event_loop_post(struct event_loop *event_loop, enum event_type type, void *context, int param1, volatile uint32_t *info);

#endif
