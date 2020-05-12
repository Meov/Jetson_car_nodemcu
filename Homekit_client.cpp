#include "Homekit_client.h"
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t name;
extern "C" void led_toggle();
extern "C" void accessory_init();
uint32_t next_heap_millis = 0;
Homekit_client::Homekit_client(/* args */)
{
}
Homekit_client::~Homekit_client()
{
}
void Homekit_client::homekit_loop() {
	arduino_homekit_loop();
	uint32_t time = millis();
	if (time > next_heap_millis) {
		INFO("heap: %d, sockets: %d", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
		next_heap_millis = time + 5000;
	}
}

void Homekit_client::homekit_setup() {
	accessory_init();
	uint8_t mac[WL_MAC_ADDR_LENGTH];
	WiFi.macAddress(mac);
	int name_len = snprintf(NULL, 0, "%s_%02X%02X%02X", name.value.string_value, mac[3], mac[4], mac[5]);
	char *name_value = (char*)malloc(name_len + 1);
	snprintf(name_value, name_len + 1, "%s_%02X%02X%02X", name.value.string_value, mac[3], mac[4], mac[5]);
	name.value = HOMEKIT_STRING_CPP(name_value);
	arduino_homekit_setup(&config);
}
