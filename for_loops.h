// Modern-style for loops

#ifndef FOR_LOOPS
#define FOR_LOOPS

#define for_times(name, times) for (name = 0; name < times; name++)
#define for_range(name, start, end) for (name = start; name < end; name++)
#define for_range_step(name, start, end, step) for (name = start; name < end; name += step)

// Iterates through all the characters in a string
#define for_char(name, str) while ((name = *str++) != 0)

// Iterates through a list until a certain value is reached.
#define for_list_till(name, list, till) while ((name = *list++) != till)

// Iterates through a list while a predicate returns true.
#define for_list_untill(name, list, untill) while (!until(name = *list++))

#endif // !FOR_LOOPS