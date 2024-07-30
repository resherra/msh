#include "init.h"

const char *format_type(int type)
{
	switch (type) {
		case D_QUOTE:
			return "D_QUOTE";
		case S_QUOTE:
			return "S_QUOTE";
		case SPACE:
			return "SPACE";
		case ENV:
			return "ENV";
		case PIPE:
			return "PIPE";
		case RED_IN:
			return "RED_IN";
		case RED_OUT:
			return "RED_OUT";
		case RED_APP:
			return "RED_APP";
		case HERE_DOC:
			return "HERE_DOC";
		default:
			return "WORD"; // Default case
	}
}

const char *format_state(int type)
{
	switch (type) {
		case IN_DOUBLE_Q:
			return "IN_DOUBLE_Q";
		case IN_S_QUOTE:
			return "IN_S_QUOTE";
		default:
			return "GENERAL"; // Default case
	}
}