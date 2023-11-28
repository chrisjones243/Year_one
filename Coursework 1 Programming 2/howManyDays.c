#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int howManyDays() {
    int fromYear = 1401;
    int toYear = 1800;

    int MondaysOnTwelth = 0;

    for ( ; fromYear <= toYear; fromYear++) {
        for (int month = 1; month <= 12; month++){
            // Use's Zeller's congruence to find the day of the week of the 12th of every month
            int j = floor(fromYear/100);
            int k = fromYear % 100;
            int h = (int)(12 + floor((13 * (month + 1)) / 5) + k + floor(k/4) + floor(j/4) + 5 * j) % (int)7;
            // If the day of the week is a Tuesday, increment the counter.
            // 0 = Saturday, 1 = Sunday, 2 = Monday, 3 = Tuesday, 4 = Wednesday, 5 = Thursday, 6 = Friday
            // Since we assume that 18th May 2007 is a Tuesday, even though it was a friday, we change the above to
            // 4 = Sunday, 5 = Monday, 6 = Tuesday, 0 = Wednesday, 1 = Thursday, 2 = Friday, 3 = Saturday
            if (h == 5) {
                MondaysOnTwelth++;
            }
        }
    }
    printf("There are %d Tuesdays on the 12th of a month between 1401 and 1800", MondaysOnTwelth);
    return MondaysOnTwelth;
}

int main() {
    howManyDays();
    return 0;
};