#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "app_dbg.h"
#include "giec_api_gpio.h"
#include "task_list.h"
#include "timer.h"

q_msg_t gw_task_gpio_mailbox;

void *gw_task_gpio_entry(void *) {
    ak_msg_t *msg = AK_MSG_NULL;
    wait_all_tasks_started();
    APP_DBG("[STARTED] gw_task_gpio_entry\n");

    fca_led_status_t led_cfg;

    while (1) {
        /* get messge */
        msg = ak_msg_rev(GW_TASK_GPIO_ID);

        switch (msg->header->sig) {
            case GW_GPIO_LIGHTNING_WHITE_REQ: {
                APP_DBG("GW_GPIO_LIGHTNING_WHITE_REQ\n");
                static bool state_white = 1;
                fca_set_led_lighting(FCA_LIGHTING_LED_WHITE, state_white);
                APP_DBG("State lightning: %d\n", state_white);
                state_white = state_white == 1 ? 0 : 1;
            } break;

            case GW_GPIO_LIGHTNING_IR_REQ: {
                APP_DBG("GW_GPIO_LIGHTNING_IR_REQ\n");
                static bool state_ir = 1;
                fca_set_led_lighting(FCA_LIGHTING_LED_IR, state_ir);
                APP_DBG("State ir: %d\n", state_ir);
                state_ir = state_ir == 1 ? 0 : 1;
            } break;

            case GW_GPIO_LED_WHITE_REQ: {
                APP_DBG("GW_GPIO_LED_WHITE_REQ\n");
                static bool state = 1;
                led_cfg.color = FCA_LED_COLOR_WHITE;
                led_cfg.mode = (FCA_LED_MODE_E)state;
                led_cfg.interval = 0;
                state = state == FCA_LED_MODE_ON ? FCA_LED_MODE_OFF : FCA_LED_MODE_ON;

                fca_gpio_led_status_set(led_cfg);
            } break;

            case GW_GPIO_LED_YELLOW_REQ: {
                APP_DBG("GW_GPIO_LED_YELLOW_REQ\n");
                static bool state = 1;
                led_cfg.color = FCA_LED_COLOR_YELLOW;
                led_cfg.mode = (FCA_LED_MODE_E)state;
                led_cfg.interval = 0;
                state = state == FCA_LED_MODE_ON ? FCA_LED_MODE_OFF : FCA_LED_MODE_ON;
                fca_gpio_led_status_set(led_cfg);
            } break;

            case GW_GPIO_LED_MAX_REQ: {
                APP_DBG("GW_GPIO_LED_YELLOW_REQ\n");
                static bool state = 1;
                led_cfg.color = FCA_LED_COLOR_MAX;
                led_cfg.mode = (FCA_LED_MODE_E)state;
                led_cfg.interval = 0;
                state = state == FCA_LED_MODE_ON ? FCA_LED_MODE_OFF : FCA_LED_MODE_ON;
                fca_gpio_led_status_set(led_cfg);
            } break;

            case GW_GPIO_LED_WHITE_BLINK_REQ: {
                APP_DBG("GW_GPIO_LED_BLINK_REQ\n");
                try {
                    int itv = std::stoi(
                        string((char *)msg->header->payload, msg->header->len));
                    led_cfg.color = FCA_LED_COLOR_WHITE;
                    led_cfg.mode = FCA_LED_MODE_BLINKING;
                    led_cfg.interval = itv;
                    fca_gpio_led_status_set(led_cfg);
                } catch (const std::exception &e) {
                    APP_DBG("%s\n", e.what());
                }

            } break;

            case GW_GPIO_LED_YELLOW_BLINK_REQ: {
                APP_DBG("GW_GPIO_LED_YELLOW_BLINK_REQ\n");
                try {
                    int itv = std::stoi(
                        string((char *)msg->header->payload, msg->header->len));
                    led_cfg.color = FCA_LED_COLOR_YELLOW;
                    led_cfg.mode = FCA_LED_MODE_BLINKING;
                    led_cfg.interval = itv;
                    fca_gpio_led_status_set(led_cfg);
                } catch (const std::exception &e) {
                    APP_DBG("%s\n", e.what());
                }
            } break;

            case GW_GPIO_LED_MAX_BLINK_REQ: {
                APP_DBG("GW_GPIO_LED_MAX_BLINK_REQ\n");
                try {
                    int itv = std::stoi(
                        string((char *)msg->header->payload, msg->header->len));
                    led_cfg.color = FCA_LED_COLOR_MAX;
                    led_cfg.mode = FCA_LED_MODE_BLINKING;
                    led_cfg.interval = itv;
                    fca_gpio_led_status_set(led_cfg);
                } catch (const std::exception &e) {
                    APP_DBG("%s\n", e.what());
                }
            } break;

            case GW_GPIO_LED_WHITE_OFF_REQ: {
                APP_DBG("GW_GPIO_LED_WHITE_OFF_REQ\n");
				led_cfg.color = FCA_LED_COLOR_WHITE;
                led_cfg.mode = FCA_LED_MODE_OFF;
                fca_gpio_led_status_set(led_cfg);
            } break;

			case GW_GPIO_LED_YELLOW_OFF_REQ: {
                APP_DBG("GW_GPIO_LED_YELLOW_OFF_REQ\n");
				led_cfg.color = FCA_LED_COLOR_YELLOW;
                led_cfg.mode = FCA_LED_MODE_OFF;
                fca_gpio_led_status_set(led_cfg);
            } break;

            default:
                break;
        }

        /* free message */
        ak_msg_free(msg);
    }

    return (void *)0;
}
