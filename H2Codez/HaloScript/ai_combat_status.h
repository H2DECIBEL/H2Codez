#pragma once

enum ai_combat_statuses
{
	unk_0,
	idle,
	alert,
	active,
	uninspected,
	definite,
	certain,
	visible,
	clear_los,
	dangerous
};

constexpr static char *ai_combat_statuses_names[] = {
	"unk_0",
	"idle",
	"alert",
	"active",
	"uninspected",
	"definite",
	"certain",
	"visible",
	"clear_los",
	"dangerous"
};
