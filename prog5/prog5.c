#include <stdio.h>

/* Structure containing bitfields */
struct field
{
    unsigned int your_choice          : 1;
    unsigned int your_mothers_choice  : 1;
    unsigned int your_fathers_choice  : 1;
    unsigned int socially_acceptable  : 1;
    unsigned int financially_viable   : 1;
    unsigned int do_you_have_aptitude : 1;
    unsigned int do_you_like_it       : 1;
    unsigned int decision             : 1;
};

/* Union */
union decision
{
    unsigned char flags;
    struct field bits;
};

/* Function Prototypes */
union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main()
{
    union decision d;

    d = input();

    make_decision(&d);

    print_decision(d);

    print_conclusion_based_on_flags(d);

    return 0;
}

/* Function to take input */
union decision input()
{
    union decision d;

    int temp;

    d.flags = 0;

    printf("Enter 1 for YES and 0 for NO\n");

    printf("Is it your choice? ");
    scanf("%d", &temp);
    d.bits.your_choice = temp;

    printf("Does your mother support it? ");
    scanf("%d", &temp);
    d.bits.your_mothers_choice = temp;

    printf("Does your father support it? ");
    scanf("%d", &temp);
    d.bits.your_fathers_choice = temp;

    printf("Is it socially acceptable? ");
    scanf("%d", &temp);
    d.bits.socially_acceptable = temp;

    printf("Is it financially viable? ");
    scanf("%d", &temp);
    d.bits.financially_viable = temp;

    printf("Do you have aptitude for it? ");
    scanf("%d", &temp);
    d.bits.do_you_have_aptitude = temp;

    printf("Do you like it? ");
    scanf("%d", &temp);
    d.bits.do_you_like_it = temp;

    return d;
}

/* Function to compute decision */
void make_decision(union decision *d)
{
    d->bits.decision =
    (
        d->bits.your_choice &&
        d->bits.do_you_like_it &&
        d->bits.do_you_have_aptitude &&
        d->bits.financially_viable
    );
}

/* Function to print report */
void print_decision(union decision d)
{
    printf("\n------ DECISION REPORT ------\n");

    printf("Your Choice         : %s\n",
           d.bits.your_choice ? "YES" : "NO");

    printf("Mother Supports     : %s\n",
           d.bits.your_mothers_choice ? "YES" : "NO");

    printf("Father Supports     : %s\n",
           d.bits.your_fathers_choice ? "YES" : "NO");

    printf("Socially Acceptable : %s\n",
           d.bits.socially_acceptable ? "YES" : "NO");

    printf("Financially Viable  : %s\n",
           d.bits.financially_viable ? "YES" : "NO");

    printf("Aptitude Present    : %s\n",
           d.bits.do_you_have_aptitude ? "YES" : "NO");

    printf("You Like It         : %s\n",
           d.bits.do_you_like_it ? "YES" : "NO");

    printf("Final Decision      : %s\n",
           d.bits.decision ? "GO AHEAD" : "RECONSIDER");
}

/* Function using flags */
void print_conclusion_based_on_flags(union decision d)
{
    printf("\n------ FLAGS ANALYSIS ------\n");

    printf("Flags Value = %u\n", d.flags);

    if(d.flags > 200)
    {
        printf("Strong positive alignment.\n");
    }
    else if(d.flags > 100)
    {
        printf("Moderately positive decision.\n");
    }
    else
    {
        printf("Decision needs deeper thinking.\n");
    }
}