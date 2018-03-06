#ifndef DM_EXPORT_H
#define DM_EXPORT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DM_PRODUCT_KEY        "a1AzoSi5TMc"
#define DM_DEVICE_NAME        "test_light_for_iotx_dm_cmp_dev"
#define DM_DEVICE_SECRET      "Hl1UjJIBXo3AzjLhYdtWEGwSllHCyBpm"
#define DM_DEVICE_ID          "IoTxHttpTestDev_001"

#define DM_IMPL_CLASS get_dm_impl_class()

typedef struct {
    const void*  _;
    void*        _logger;
    char*        _name; /* dm thing manager object name. */
    int          _get_tsl_from_cloud;
    void*        _thing_manager; /* thing manager object */
    int          _log_level;
    int          _domain_type;
} dm_impl_t;


typedef enum {
    dm_callback_type_property_value_set = 0,
    dm_callback_type_service_requested,
    dm_callback_type_cloud_connected,
    dm_callback_type_cloud_disconnected,
    dm_callback_type_new_thing_created,
    dm_callback_type_thing_disabled,
    dm_callback_type_thing_enabled,
    dm_callback_type_raw_data_arrived,

    dm_callback_type_number,
} dm_callback_type_t;

typedef void (*handle_dm_callback_fp_t)(dm_callback_type_t callback_type, void* thing_id,
                                        const char* property_service_identifier, int request_id,
                                        void* raw_data, int raw_data_length);

/* domain type */
typedef enum {
    /* iot-as-mqtt.cn-shanghai.aliyuncs.com */
    dm_cloud_domain_sh,
    /* USA */
    dm_cloud_domain_usa,

    dm_cloud_domain_max,
} dm_cloud_domain_type_t;

typedef struct {
    size_t size;
    const char*  _class_name;
    void* (*ctor)(void* _self, va_list* params);
    void* (*dtor)(void* _self);
    void* (*generate_new_thing)(void* _self, const char* tsl, int tsl_len);
    int   (*set_property_value)(void* _self, const void* thing_id, const void* identifier, const void* value, const char* value_str);
    int   (*set_event_output_value)(void* _self, const void* thing_id, const void* identifier, const void* value, const char* value_str);
    int   (*set_service_output_value)(void* _self, const void* thing_id, const void* identifier, const void* value, const char* value_str);
    int   (*get_property_value)(const void* _self, const void* thing_id, const void* identifier, void* value, char** value_str);
    int   (*get_service_input_value)(const void* _self, const void* thing_id, const void* identifier, void* value, char** value_str);
    int   (*get_service_output_value)(const void* _self, const void* thing_id, const void* identifier, void* value, char** value_str);
    int   (*get_event_output_value)(const void* _self, const void* thing_id, const void* identifier, void* value, char** value_str);
    int   (*install_callback_function)(void* _self, handle_dm_callback_fp_t linkkit_callback_fp);
    int   (*trigger_event)(const void* _self, const void* thing_id, const void* event_identifier, const char* property_identifier);
    int   (*answer_service)(const void* _self, const void* thing_id, const void* identifier, int response_id, int code);
    int   (*invoke_raw_service)(const void* _self, const void* thing_id, void* raw_data, int raw_data_length);
    int   (*answer_raw_service)(const void* _self, const void* thing_id, void* raw_data, int raw_data_length);
#ifndef CMP_SUPPORT_MULTI_THREAD
    int   (*yield)(const void* _self, int timeout_ms);
#endif
} dm_t;

extern const void* get_dm_impl_class();


extern void* new_object(const void* _class, ...);
extern void  delete_object(void* _class);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DM_EXPORT_H */