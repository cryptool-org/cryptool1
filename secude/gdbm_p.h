/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 *	src/gdbm
 */


typedef void (* fatal_func_t)();

gdbm_file_info SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV gdbm_open SEC_PROTOTYPE_5(
	char *		, file,
	int		, block_size,
	int		, read_write,
	int		, mode,
	fatal_func_t	, fatal_func
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_put_av_elem SEC_PROTOTYPE_3(
	avail_elem 	, new_el,
	avail_elem *	, av_table,
	int *		, av_count
);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_new_bucket SEC_PROTOTYPE_3(
	
	gdbm_file_info	 *	, dbf,
	
	hash_bucket	 *	, bucket,
	
	int		  	, bits

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_get_bucket SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	long		  	, dir_index

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_split_bucket SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	int		  	, next_insert

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_write_bucket SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	cache_elem	 *	, ca_entry

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_close SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_delete SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_dirfno SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_fetch SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbminit SEC_PROTOTYPE_1(
	
	char	 *	, file

);

gdbm_file_info SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV dbm_open SEC_PROTOTYPE_3(
	
	char	 *	, file,
	
	int	  	, flags,
	
	int	  	, mode

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_pagfno SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_firstkey SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_nextkey SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dbm_store SEC_PROTOTYPE_4(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key,
	
	datum		  	, content,
	
	int		  	, flags

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV delete_ SEC_PROTOTYPE_1(
	
	datum	  	, key

);

long SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_alloc SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	int		  	, num_bytes

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_free SEC_PROTOTYPE_3(
	
	gdbm_file_info	 *	, dbf,
	
	long		  	, file_adr,
	
	int		  	, num_bytes

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV fetch SEC_PROTOTYPE_1(
	
	datum	  	, key

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV _gdbm_read_entry SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	int		  	, elem_loc

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_findkey SEC_PROTOTYPE_4(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key,
	
	char		**	, dptr,
	
	long		 *	, new_hash_val

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_close SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_delete SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_fetch SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_reorganize SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_firstkey SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_nextkey SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gdbm_store SEC_PROTOTYPE_4(
	
	gdbm_file_info	 *	, dbf,
	
	datum		  	, key,
	
	datum		  	, content,
	
	int		  	, flags

);

long SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_hash SEC_PROTOTYPE_1(
	
	datum	  	, key

);

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV firstkey SEC_PROTOTYPE_0();

datum SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV nextkey SEC_PROTOTYPE_1(
	
	datum	  	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV store SEC_PROTOTYPE_2(
	
	datum	  	, key,
	
	datum	  	, content

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV print_bucket SEC_PROTOTYPE_2(
	
	hash_bucket	 *	, bucket,
	
	char		 *	, mesg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_print_avail_list SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_print_bucket_cache SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_end_update SEC_PROTOTYPE_1(
	
	gdbm_file_info	 *	, dbf

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV _gdbm_fatal SEC_PROTOTYPE_2(
	
	gdbm_file_info	 *	, dbf,
	
	char		 *	, val

);

/* strcase.c : */
/* so funktionieren die Prototypen mit gnu (PC) : */





#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


