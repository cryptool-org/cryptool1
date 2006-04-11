
#ifndef SENF_P_H_
#define SENF_P_H_

#if !defined(SECUDE_SENF_INCLUDE) || !SECUDE_SENF_INCLUDE
#error do not include this file, include <secude/senf.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_ulong;
senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_features;
senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_version;
senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_cstring;
senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_error;
senf_data_func SEC_GLOBAL_FUNC_PREFIX senf_get_selector_list;

senf_free_func SEC_GLOBAL_FUNC_PREFIX senf_free_generic;

senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_ulong;
senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_features;
senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_version;
senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_cstring;
senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_error;
senf_sprint_func SEC_GLOBAL_FUNC_PREFIX senf_sprint_selector_list;

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV senf_cat_string SEC_PROTOTYPE_2(
	char *, string,
	const char *, msg
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_get SEC_PROTOTYPE_4(
	senf_data **, data,
	senf_selector, api,
	senf_selector, selector,
	senf_type, type
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_get_data SEC_PROTOTYPE_1(
	senf_data *, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_set SEC_PROTOTYPE_4(
	senf_selector, api,
	senf_selector, selector,
	const void *, value,
	senf_type, type
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_set_data SEC_PROTOTYPE_1(
	senf_data *, data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV senf_sprint SEC_PROTOTYPE_2(
	char *, string,
	const senf_data *, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_fprint SEC_PROTOTYPE_2(
	FILE *, f,
	const senf_data *, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_print SEC_PROTOTYPE_1(
	const senf_data *, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_free SEC_PROTOTYPE_1(
	senf_data **, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_free_data SEC_PROTOTYPE_1(
	senf_data *, data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_alias2selector SEC_PROTOTYPE_3(
	senf_selector *, sel,
	senf_selector, api,
	const char *, alias
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV senf_sprint_alias SEC_PROTOTYPE_3(
	char *, string,
	senf_selector, api,
	senf_selector, selector
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_fprint_alias SEC_PROTOTYPE_3(
	FILE *, f,
	senf_selector, api,
	senf_selector, selector
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_print_alias SEC_PROTOTYPE_2(
	senf_selector, api,
	senf_selector, selector
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV senf_sprint_description SEC_PROTOTYPE_3(
	char *, string,
	senf_selector, api,
	senf_selector, selector
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_fprint_description SEC_PROTOTYPE_3(
	FILE *, f,
	senf_selector, api,
	senf_selector, selector
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_print_description SEC_PROTOTYPE_2(
	senf_selector, api,
	senf_selector, selector
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_register_api SEC_PROTOTYPE_3(
	const senf_api_selector *, api,
	senf_unregister_func *, unregister,
	void *, context
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_reregister_api SEC_PROTOTYPE_3(
	const senf_api_selector *, api,
	senf_unregister_func *, unregister,
	void *, context
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_unregister_api SEC_PROTOTYPE_1(
	senf_selector, api
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV senf_list_selector SEC_PROTOTYPE_4(
	FILE *, f,
	senf_selector, api,
	senf_selector, sel,
	unsigned long, flags
);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* SENF_P_H_ */

