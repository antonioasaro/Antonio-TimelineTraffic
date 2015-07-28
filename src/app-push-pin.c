#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_text_layer;
static bool action_launch = S_FALSE;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
//  GRect bounds = layer_get_bounds(window_layer);

  APP_LOG(APP_LOG_LEVEL_WARNING, "windows_load()");
  s_text_layer = text_layer_create(GRect(0, 10, 144, 168));
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_text_layer, GTextOverflowModeWordWrap);
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_background_color(s_text_layer, GColorClear);
  if (action_launch) {
	  text_layer_set_text(s_text_layer, "Kick off action");
    } else {
	  text_layer_set_text(s_text_layer, "See the app logs to check the insert success.\n\n Check the timeline after ~15s to see the pin!");
  }
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
}

#define LAUNCH_ARG_CANCEL 15
#define LAUNCH_ARG_REVIEW 22
static void launched() {
  if(launch_reason() == APP_LAUNCH_TIMELINE_ACTION) {
  uint32_t arg = launch_get_args();
  action_launch = S_TRUE;

  switch(arg) {
    case LAUNCH_ARG_CANCEL:
	  // Cancel table UI...
	  APP_LOG(APP_LOG_LEVEL_WARNING, "launched.LAUNCH_ARG_CANCEL");
      break;
    case LAUNCH_ARG_REVIEW:
      // Leave a review UI...
	  APP_LOG(APP_LOG_LEVEL_WARNING, "launched.LAUNCH_ARG_REVIEW");
      break;
    }
  }
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorFolly);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  launched();
  init();
  app_event_loop();
  deinit();
}

/***************************************
{
  "id": "antonio-cloudpebble-test-pin-1",
  "time": "2015-07-27T22:00:00Z",
  "layout": {
    "type": "genericPin",
    "title": "Antonio Pin!!"
  },
  "actions": [
    {
      "title": "View Schedule",
      "type": "openWatchApp",
      "launchCode": 15
    },
    {
      "title": "Show Directions",
      "type": "openWatchApp",
      "launchCode": 22
    }
 
  ]
}

*****************************************/