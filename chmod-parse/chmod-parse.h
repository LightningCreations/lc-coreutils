//
// Created by chorm on 2020-07-22.
//

#ifndef LCNIX_CHMOD_PARSE_H
#define LCNIX_CHMOD_PARSE_H

#include <sys/types.h>

/**
 * Parses a textual or octal mode according to the handling specified by chmod(1).
 * An octal mode is a set of 1 to 4 octal digits, optionally preceeded by +, -, or =.
 *  The mode is interpreted from those digits exactly, with unset digits being treated as 0.
 *  If no operator is specified for an octal mode, a directories unmentioned suid and sgid bits will be unaffected.
 *
 * A textual mode is a string of the form [u|g|o|a](+|-|=)(u|g|o|(r|w|X|x|s|t)...). Multiple textual modes can be specified, separated by commas.
 *  The first character is the type selector, u is the owning user, g is the owning group, o is other users, and a is all types.
 *   If omitted, the effect is the same as a, but the bits mentioned in the umask parameter are not affected.
 *
 *  The second character is the operator, + is add, - is remove, = is set.
 *
 *  The last set of characters is the permissions. If the permissions are either u, g, or o,
 *   then the permissions already present in that selector are copied based on the type selector.
 *  Otherwise, the permissions are the bits to affect.
 *  r is the "readable" bit, w is the "writable" bit, x is the "executable" bit,
 *   t is the "sticky" or "secure-delete" bit (when the type is o, a, or omitted),
 *   s is the set-uid bit and/or the set-gid bit (when type is u (suid), g (sgid), a or omitted (both suid and sgid)),
 *  X affects the "executable" bit if either the file is a directory, or any type in the incoming mode has the executable bit set.
 *
 * If multiple textual modes are provided, they modify the incoming mode in order, and apply to the modified incoming mode.
 *
 * If mode contains any bits other than permission bits (specifically, type information), that is preserved by this function.
 *
 * If the parsed mode is invalid, returns -1, and errno is set to EINVAL.
 *
 * @param md The mode string to parse
 * @param mode The incoming mode to modify.
 * @param dir Whether or not the mode computed is for a directory.
 * @param umask The exclusion mask to apply for textual modes when the type is omitted.
 * @return The final computed mode
 */
mode_t parse_mode(const char* md,mode_t mode,_Bool dir,mode_t umask);

#endif //LCNIX_CHMOD_PARSE_H
