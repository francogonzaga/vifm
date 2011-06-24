#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/keys.h"
#include "../../src/modes.h"

#include "buildin_keys.h"

#ifdef TEST
#define printf(...)
#endif

static int* mode;

static void keys_m(struct key_info key_info, struct keys_info *keys_info);
static void keys_quote(struct key_info key_info, struct keys_info *keys_info);
static void keys_H(struct key_info key_info, struct keys_info *keys_info);
static void keys_j(struct key_info key_info, struct keys_info *keys_info);
static void keys_k(struct key_info key_info, struct keys_info *keys_info);
static void keys_s(struct key_info key_info, struct keys_info *keys_info);
static void keys_i(struct key_info key_info, struct keys_info *keys_info);
static void keys_if(struct key_info key_info, struct keys_info *keys_info);
static void keys_delete(struct key_info key_info, struct keys_info *keys_info);
static void keys_delete_selector(struct key_info key_info,
		struct keys_info *keys_info);
static void keys_v(struct key_info key_info, struct keys_info *keys_info);
static void keys_quit(struct key_info key_info, struct keys_info *keys_info);

void
init_buildin_keys(int *key_mode)
{
	struct key_t *curr;

	assert(key_mode != NULL);

	mode = key_mode;

	curr = add_cmd(L"m", NORMAL_MODE);
	curr->type = BUILDIN_WAIT_POINT;
	curr->data.handler = keys_m;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_cmd(L"'", NORMAL_MODE);
	curr->type = BUILDIN_WAIT_POINT;
	curr->data.handler = keys_quote;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_selector(L"'", NORMAL_MODE);
	curr->type = BUILDIN_WAIT_POINT;
	curr->data.handler = keys_quote;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_cmd(L"H", NORMAL_MODE);
	curr->data.handler = keys_H;

	curr = add_cmd(L"j", NORMAL_MODE);
	curr->data.handler = keys_j;

	curr = add_selector(L"j", NORMAL_MODE);
	curr->data.handler = keys_j;

	curr = add_cmd(L"j", VISUAL_MODE);
	curr->data.handler = keys_j;

	curr = add_selector(L"j", VISUAL_MODE);
	curr->data.handler = keys_j;

	curr = add_cmd(L"k", NORMAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"k", NORMAL_MODE);
	curr->data.handler = keys_k;

	curr = add_cmd(L"k", VISUAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"k", VISUAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"s", NORMAL_MODE);
	curr->data.handler = keys_s;

	curr = add_selector(L"s", VISUAL_MODE);
	curr->data.handler = keys_s;

	curr = add_cmd(L"i", NORMAL_MODE);
	curr->data.handler = keys_i;

	curr = add_selector(L"if", NORMAL_MODE);
	curr->data.handler = keys_if;

	curr = add_selector(L"if", VISUAL_MODE);
	curr->data.handler = keys_if;

	curr = add_cmd(L"o", NORMAL_MODE);
	curr->type = BUILDIN_CMD;
	curr->data.cmd = wcsdup(L":only");

	curr = add_cmd(L"v", NORMAL_MODE);
	curr->type = BUILDIN_CMD;
	curr->data.cmd = wcsdup(L":vsplit");

	curr = add_cmd(L"d", NORMAL_MODE);
	curr->type = BUILDIN_WAIT_POINT;
	curr->data.handler = keys_delete_selector;
	curr->followed = FOLLOWED_BY_SELECTOR;

	curr = add_cmd(L"dd", NORMAL_MODE);
	curr->data.handler = keys_delete;

	curr = add_cmd(L"v", NORMAL_MODE);
	curr->data.handler = keys_v;

	curr = add_cmd(L"v", VISUAL_MODE);
	curr->data.handler = keys_v;

	curr = add_cmd(L"ZZ", NORMAL_MODE);
	curr->data.handler = keys_quit;

	curr = add_cmd(L"ZZ", VISUAL_MODE);
	curr->data.handler = keys_quit;
}

static void
keys_m(struct key_info key_info, struct keys_info *keys_info)
{
	printf("(%d)m in register '%c' with multikey '%c'\n",
			key_info.count, key_info.reg, key_info.multi);
}

static void
keys_quote(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)' in register '%c' with multikey '%c'\n",
			key_info.count, key_info.reg, key_info.multi);
}

static void
keys_H(struct key_info key_info, struct keys_info *keys_info)
{
	wchar_t **list, **p;
	list = list_cmds(NORMAL_MODE);

	if(list == NULL)
	{
		printf("%s\n", "error");
		return;
	}
	
	p = list;
	while(*p != NULL)
	{
		printf("%ls\n", *p);
		free(*p++);
	}
	free(list);
}

static void
keys_j(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)j in register %c\n", key_info.count, key_info.reg);
}

static void
keys_k(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)k in register %c\n", key_info.count, key_info.reg);
}

static void
keys_s(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)s in register %c\n", key_info.count, key_info.reg);
}

static void
keys_i(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)i in register %c\n", key_info.count, key_info.reg);
}

static void
keys_if(struct key_info key_info, struct keys_info *keys_info)
{
	if(keys_info->selector)
	{
		printf("as a selector: ");
	}
	printf("(%d)if in register %c\n", key_info.count, key_info.reg);
}

static void
keys_delete(struct key_info key_info, struct keys_info *keys_info)
{
	printf("(%d)delete in register %c\n", key_info.count, key_info.reg);
}

static void
keys_delete_selector(struct key_info key_info,
		struct keys_info *keys_info)
{
	printf("(%d)delete with selector in register %c\n", key_info.count,
			key_info.reg);
}

static void
keys_v(struct key_info key_info, struct keys_info *keys_info)
{
	*mode = (*mode == NORMAL_MODE) ? VISUAL_MODE : NORMAL_MODE;
	printf("v visual mode toggle\n");
}

static void
keys_quit(struct key_info key_info, struct keys_info *keys_info)
{
	printf("(%d)quit in register %c\n", key_info.count, key_info.reg);
}

/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 noexpandtab : */