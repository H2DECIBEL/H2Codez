#pragma once
#include "BlamBaseTypes.h"

struct tag_field
{
	enum field_type : size_t
	{
		string,
		long_string,
		string_id,
		old_string_id,
		char_integer,
		short_integer,
		long_integer,
		angle,
		tag,
		char_enum,
		generic_enum,
		long_enum,
		long_flags,
		word_flags,
		byte_flags,
		point_2d,
		rectangle_2d,
		rgb_color,
		argb_color,
		real,
		real_fraction,
		real_point_2d,
		real_point_3d,
		real_vector_2d,
		real_vector_3d,
		real_quaternion,
		real_euler_angles_2d,
		real_euler_angles_3d,
		real_plane_2d,
		real_plane_3d,
		real_rgb_color,
		real_argb_color,
		real_hsv_color,
		real_ahsv_color,
		short_bounds,
		angle_bounds,
		real_bounds,
		real_fraction_bounds,
		tag_reference,
		block,
		long_block_flags,
		word_block_flags,
		byte_block_flags,
		char_block_index1,
		char_block_index2,
		short_block_index1,
		short_block_index2,
		long_block_index1,
		long_block_index2,
		data,
		vertex_buffer,
		array_start,
		array_end,
		pad,
		useless_pad,
		skip,
		explanation,
		custom,
		struct_,
		terminator,

		count,
	} type;
	editor_string name;
	void *defintion;
	blam_tag group_tag;
};

CHECK_STRUCT_SIZE(tag_field, 4 * 4);

struct s_tag_field_set_version_upgrade_arguments {
	size_t set_index;
	tag_field* set_fields;
	size_t set_count;
	size_t set_size;
	void* address;
};
typedef bool (__cdecl* proc_tag_field_set_version_upgrade)(
	s_tag_field_set_version_upgrade_arguments _old,
	s_tag_field_set_version_upgrade_arguments _new
	);

struct s_tag_field_set_version
{
	tag_field* fields;
	size_t index;
	proc_tag_field_set_version_upgrade proc_upgrade;
	size_t padding;
	size_t size_of; // set to -1 when unused, else set to a value to override the field-set's calculated size_of
};

struct s_tag_field_set_runtime_data
{
	long flags;
	tag_field* fields; // contains the combined (read: with any parents) tag fields
	size_t runtime_size;
	size_t total_useless_pad_size;
};
CHECK_STRUCT_SIZE(s_tag_field_set_runtime_data, 4 * 4);

struct tag_field_set
{
	s_tag_field_set_version version;
	size_t size;					// 0x14
	size_t alignment_bit;			// 0x18
	size_t parent_version_index;		// 0x1C
	tag_field* fields;				// 0x20
	const char *size_string;			// 0x24

	const char *byteswap_name;
	size_t byteswapped_size;
	void *byteswapped_def;
	blam_tag byteswap_tag;
	size_t unk;

	s_tag_field_set_runtime_data runtime_info;
};
CHECK_STRUCT_SIZE(tag_field_set, 0x4C);

struct tag_block_defintions
{
	const char *name;
	const char *internal_name;
	size_t flags;
	size_t max_count;
	const char *max_count_str;
	tag_field_set *verions;
	size_t version_count;
	tag_field_set *latest;
	size_t padding;
	void *postprocessing_proc;
	void *format_proc;
	void *new_proc;
	void *dispose_element_proc;
};

typedef bool (__cdecl* proc_tag_group_postprocess)(INT16 tag_index, bool for_editor);
typedef bool (__cdecl* proc_tag_group_postprocess_for_sync)(INT16 tag_index, void* cache_file_writer);
typedef void (__cdecl* proc_tag_group_save_preprocess)(INT16 tag_index); // TODO: verify return type

struct tag_def
{
	const char *name;
	size_t flags;
	blam_tag group_tag;
	blam_tag parent_group_tag;
	__int16 version;
	__int8 initialized;
	__int8 padding;
	proc_tag_group_postprocess postprocess_proc;
	proc_tag_group_save_preprocess save_preprocess_proc;
	proc_tag_group_postprocess_for_sync	postprocess_for_sync_proc;
	size_t padding2;
	tag_block_defintions *block_defs;
	blam_tag child_group_tags[16];
	__int16 child_count;
	__int16 padding3;
	char *default_tag_path;
};
