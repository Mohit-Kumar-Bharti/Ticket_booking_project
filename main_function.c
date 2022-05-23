#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void busList();
void bookSeat(int);
void initiate();
void vline();
void home();
void showBus(int);
void display_ticket(int, int);
void cancel(int);
int hash_key(char *);
void bus_key();
int M = 1000000007;
// O(log b)
long long int mod_exp(long long int a, long long int b, long long int c)
{

    long long int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % c;
        b /= 2;
        a = (a * a) % c;
    }
    return (ans % c);
}

int hash[100];
char buses[10][100] = {"Delhi to Patna", "Patna to Delhi", "Hyderabad to Chennai", "Chennai to Hyderabad", "Jalandhar to Bhopal", "Bhopal to Jalandhar", "Lucknow to Surat", "Surat to Lucknow", "Sagar to Allahabad", "Allahabad to Sagar"};
struct bus_data
{
    char arriveTime[10], departTime[10], seatno[40][40];
    int counter;
};
char driver[10][15] = {"Suresh", "Rakesh", "Manoj", "Ram Manohar", "Mahender", "Vamsi", "Bablu", "Moolchand", "Pankaj", "Rajesh"};
struct bus_data bus[10];
// O(1)
void vline()
{
    int i;
    for (i = 0; i < 20; i++)
    {
        printf("*");
    }
}

// O(1)
int max(int a, int b)
{
    return a > b ? a : b;
}
int nn = 10;
int v[10];
int seg[40];
// O(no of bus * log no of bus)
//  O(no of bus * log (no of nus))
int build_seg(int ss, int se, int si)
{
    if (ss == se)
    {
        seg[si] = v[ss];
        return seg[si];
    }
    int mid = (ss + se) / 2;

    int le = build_seg(ss, mid, 2 * si + 1);
    int ri = build_seg(mid + 1, se, 2 * si + 2);

    return seg[si] = max(le, ri);
}
// O(log no of bus)
int query_seg(int l, int r, int ss, int se, int si)
{
    if (se < l || ss > r)
    {

        return INT_MIN;
    }
    if (l <= ss && r >= se)
        return seg[si];
    int mid = (ss + se) / 2;
    int le = query_seg(l, r, ss, mid, 2 * si + 1);
    int ri = query_seg(l, r, mid + 1, se, 2 * si + 2);

    return max(le, ri);
}

// O(log  no of bus)
void update_seg(int pos, int new_val, int ss, int se, int si)
{
    if (ss == se)
    {
        seg[si] = new_val;
    }
    else
    {
        int tm = (ss + se) / 2;
        if (pos <= tm)
            update_seg(pos, new_val, ss, tm, 2 * si + 1);
        else
            update_seg(pos, new_val, tm + 1, se, 2 * si + 2);
        seg[si] = max(seg[si * 2 + 1], seg[si * 2 + 2]);
    }
}
// O(no of seats + log(no of bus))
void query()
{
    int ans = query_seg(0, 9, 0, nn - 1, 0);
    printf("%d seats are available from bus 1 to bus 10\n", ans);

    int op;
    printf(" 1 to return \n \n");
    printf(" 2 to check out by range \n \n");
    printf(" 3 to check out by index \n \n");
    scanf("%d", &op);
    if (op == 1)
    {
        return;
    }
    if (op == 2)
    {
        printf("enter the range \n");
        printf("enter the leftmost bus number \n");
        int l, r;
        scanf("%d", &l);
        printf("enter the rightmost bus number \n");
        scanf("%d", &r);
        if (l >= 1 && l <= 10 && r >= 1 && r <= 10)
        {
            if (l > r)
            {
                int tem = l;
                l = r;
                r = tem;
            }

            int ans = query_seg(l - 1, r - 1, 0, nn - 1, 0);
            printf("%d seats are available \n ", ans);
            return;
        }
        else
        {
            printf("you have entered wrong range \n ");
            return;
        }
    }
    if (op == 3)
    {
        printf("how many buses are there to check \n ");
        int num;
        scanf("%d", &num);
        int ans = INT_MIN;
        while (num--)
        {
            int busno;
            printf("entert the bus number \n");
            scanf("%d", &busno);
            if (busno >= 1 && busno <= 10)
            {
                ans = max(ans, bus[busno - 1].counter);
            }
        }
        printf("%d seats are available \n", ans);
        return;
    }
    printf("wrong option selected \n");
    return;
}
// O(1)
void home()
{
    while (1)
    {
        int choice;
        printf("1.Press 1 for Buses Available \n");
        printf("2.Press 2 for reserving a seat \n");
        printf("3.Press 3 for displaying reservation information \n");
        printf("4.Press 4 for seat cancellation \n");
        printf("5.Press 5 for searching bus through names \n");
        printf("6.Press 6 for searching the maximum seats available out of all buses \n");
        printf("7.Press 7 for Exiting the Bus Reservation System\n \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            busList();
            break;
        case 2:
            bookSeat(-1);
            break;
        case 3:
            showBus(-1);
            break;
        case 4:
            cancel(-1);
            break;
        case 5:
            bus_key();
            break;
        case 6:
            query();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Wrong choice has been entered. \n \n");
        }
    }
}
// O(no of bus)
void busList()
{
    int i;
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("Press %d for \t %s \n", i + 1, buses[i]);
    }
    printf("\n \n");
}
// O(no fo seats * string length)
void bookSeat(int bus_no_key)
{
    int busno;
    if (bus_no_key == -1)
    {
        printf("\nPlease enter the bus number: ");
        scanf("%d", &busno);
        if (busno > 10 || busno <= 0)
        {
            printf("\nInvalid bus number has been entered.\n \n");
            home();
        }
    }
    else
    {
        busno = bus_no_key + 1;
    }

    {
        int nseats, seat;
        --busno;
        printf("\nSeating arrangement of bus number %d:\n\n", busno + 1);
        int i, j, k;
        for (j = 0; j < 10; j++)
        {
            for (i = 0; i < 4; i++)
            {
                printf("%d . %s \t", 4 * j + i + 1, bus[busno].seatno[4 * j + i]);
            }
            printf("\n");
        }
        printf("\n \n");
        printf("How many seats do you want to book: ");
        scanf("%d", &nseats);
        if (bus[busno].counter < nseats && bus[busno].counter != 0)
        {
            printf("\nOnly %d seats are available. \n \n", bus[busno].counter);
            printf("\nPress 1 to continue and book %d seats. \n", bus[busno].counter);
            printf("\nPress 2 to go to home page. \n");
            int op;
            printf("\nEnter your choice: ");
            scanf("%d", &op);
            printf("\n");
            if (op == 2)
                home();
        }
        for (k = 0; k < nseats; k++)
        {
            if (bus[busno].counter == 0)
            {
                printf("\nNo seats available.Sorry.\n \n");
                break;
            }
            printf("\nPlease enter the seat number: ");
            scanf("%d", &seat);
            if (seat <= 0 || seat > 40)
            {
                printf("\nInvalid seat number has been entered. Only 40 seats are available. \n \n");
                k--;
                continue;
            }
            if (strcmp(bus[busno].seatno[seat - 1], "Empty") != 0)
            {
                printf("\nThis seat is already booked.\n\n");
                k--;
                continue;
            }
            bus[busno].counter--;
            printf("\nPlease enter Passenger %d name: ", k + 1);
            scanf("%s", &bus[busno].seatno[seat - 1]);
            update_seg(busno, bus[busno].counter, 0, nn - 1, 0);

            printf("\nYour seat has successfully been reserved. \n \n");
            display_ticket(busno, seat);
        }
    }
}
// O(string len passenger name+driver's name)
void display_ticket(int busno, int seat)
{
    printf("\n \n \t \t");
    vline();
    vline();
    printf("\n");
    printf("\t \t");
    vline();
    vline();
    printf("\n");
    printf("\t Seat Reservation Details:\n \n");
    printf("\t Bus No.: %d \n \n", busno + 1);
    printf("\t Driver's name: %s \n \n", driver[busno]);
    int idx = 0;
    printf("\t From City: ");
    while (buses[busno][idx] != ' ')
    {
        printf("%c", buses[busno][idx]);
        idx++;
    }
    idx++;
    printf("\t \t To City: ");
    while (buses[busno][idx] != ' ')
    {
        idx++;
    }
    while (buses[busno][idx] != '\0')
    {
        printf("%c", buses[busno][idx]);
        idx++;
    }
    printf("\n \n");
    printf("\t Arrival Time: %c %c : %c %c hrs \t \t", bus[busno].arriveTime[0], bus[busno].arriveTime[1], bus[busno].arriveTime[2], bus[busno].arriveTime[3]);
    printf("Departure Time: %c %c : %c %c hrs \n \n", bus[busno].departTime[0], bus[busno].departTime[1], bus[busno].departTime[2], bus[busno].departTime[3]);
    printf("\t Passenger's Name: %s \n \n", bus[busno].seatno[seat - 1]);
    printf("\t Seat No.: %d \n \n", seat);
    printf("\t Your Password: %d_%d \n \n", busno + 1, seat);
    printf("\t Please remember this password in case you want to cancel your ticket. \n \n");
    printf("\t \t");
    vline();
    vline();
    printf("\n");
    printf("\t \t");
    vline();
    vline();
    printf("\n \n");
}
// O(string len of passenger name)
void cancel(int bus_no_key)
{
    int busno;
    if (bus_no_key == -1)
    {
        printf("\nPlease enter the bus number: ");
        scanf("%d", &busno);
        if (busno > 10 || busno <= 0)
        {
            printf("\nInvalid bus number has been entered.\n \n");
            home();
        }
    }
    else
    {
        busno = bus_no_key + 1;
    }

    {
        --busno;
        char pass[5], name[10];
        printf("\nPlease enter your password: ");
        scanf("%s", &pass);
        printf("\nPlease enter passenger name: ");
        scanf("%s", &name);
        int i = 0, seat = 0;
        while (pass[i] != '_')
            i++;
        i++;
        while (pass[i] != '\0')
        {
            seat += pass[i] - '0';
            seat *= 10;
            i++;
        }
        seat /= 10;
        if (!(seat >= 1 && seat <= 40))
        {
            printf("\nInvalid credentials. We could not process the cancellation. \n \n");
            home();
        }
        if (strcmp(bus[busno].seatno[seat - 1], name) == 0)
        {
            char ch[6] = "Empty";
            int k;
            for (k = 0; k < 6; k++)
                bus[busno].seatno[seat - 1][k] = ch[k];
            bus[busno].counter++;
            update_seg(busno, bus[busno].counter, 0, nn - 1, 0);

            printf("\nYour seat has been cancelled succesfully. \n \n");
        }
        else
        {
            printf("\nInvalid credentials. We could not process the cancellation. \n \n");
        }
    }
}
void showBus(int bus_no_key)
{
    int busno;
    if (bus_no_key == -1)
    {
        printf("\nPlease enter the bus number: ");
        scanf("%d", &busno);
        if (busno > 10 || busno <= 0)
        {
            printf("\nInvalid bus number has been entered.\n \n");
            home();
        }
    }
    else
    {
        busno = bus_no_key + 1;
    }

    {
        --busno;
        printf("\nSeating arrangement of bus number %d:\n\n", busno + 1);
        int i, j, k;
        for (j = 0; j < 10; j++)
        {
            for (i = 0; i < 4; i++)
            {
                printf("%d . %s \t", 4 * j + i + 1, bus[busno].seatno[4 * j + i]);
            }
            printf("\n");
        }
        printf("\n \n");
    }
}
// O(no of bus *  log no of bus + no of bus * name of bus * log name of bus)
void initiate()
{

    for (int i = 0; i < nn; ++i)
        v[i] = 40;
    build_seg(0, nn - 1, 0);
    memset(hash, -1, sizeof(hash));
    int p;
    for (p = 0; p < 10; ++p)
    {
        int val = hash_key(buses[p]);
        while (hash[val] != -1)
        {
            val++;
            val %= 100;
        }
        hash[val] = p;
    }
    printf("\n \n \n");
    vline();
    printf(" Welcome to our Bus Reservation System! ");
    vline();
    printf("\n \n");
    int i, j, k;
    int hour = 0, minute = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 40; j++)
        {
            char ch[6] = "Empty";
            for (k = 0; k < 6; k++)
                bus[i].seatno[j][k] = ch[k];
            bus[i].counter = 40;
            hour += i;
            hour %= 24;
            minute += i * 30;
            minute %= 60;
            int t;
            for (t = 0; t < 4; t++)
            {
                bus[i].arriveTime[t] = '\0';
            }
            bus[i].arriveTime[0] = (char)((i % 100) / 10 + '0');
            bus[i].arriveTime[1] = (char)((i % 10) + '0');
            bus[i].arriveTime[2] = (char)((minute % 100) / 10 + '0');
            bus[i].arriveTime[3] = (char)((minute % 10) + '0');
            bus[i].departTime[0] = (char)(((i + 1) % 100) / 10 + '0');
            bus[i].departTime[1] = (char)(((i + 1) % 10) + '0');
            bus[i].departTime[2] = (char)(((minute + 1) % 100) / 10 + '0');
            bus[i].departTime[3] = (char)(((minute + 1) % 10) + '0');
        }
    }
}
// O(string length * log str len)
int hash_key(char *c)
{
    int n = strlen(c);
    long long int val = 0;
    int p = 31, i;
    for (i = 0; i < n; ++i)
    {
        if (c[i] >= 'a' && c[i] <= 'z')
        {
            val += (c[i] - 'a') * mod_exp(p, i, M);
            val %= M;
        }
        else if (c[i] >= 'A' && c[i] <= 'Z')
        {
            val += (c[i] - 'A') * mod_exp(p, i, M);
            val %= M;
        }
    }
    // 100 is the size
    return (val % (100));
}

// O(n1 log n1 + n2 log n2 + sigma of names of all buses)
void bus_key()
{
    char s1[100], s2[100];
    printf("\nPlease enter the starting city: ");
    scanf("%s", &s1);
    printf("\nPlease enter the destination city: ");
    scanf("%s", &s2);
    char s3[200];
    int idx = 0;
    int i = 0;
    while (s1[i] != '\0')
    {
        if (i == 0)
        {
            if (s1[i] >= 'a' && s1[i] <= 'z')
                s1[i] -= 32;
        }
        else
        {
            if (s1[i] >= 'A' && s1[i] <= 'Z')
                s1[i] += 32;
        }

        s3[idx++] = s1[i++];
    }
    s3[idx++] = ' ';
    s3[idx++] = 't';
    s3[idx++] = 'o';
    s3[idx++] = ' ';
    i = 0;
    while (s2[i] != '\0')
    {
        if (i == 0)
        {
            if (s2[i] >= 'a' && s2[i] <= 'z')
                s2[i] -= 32;
        }
        else
        {
            if (s2[i] >= 'A' && s2[i] <= 'Z')
                s2[i] += 32;
        }
        s3[idx++] = s2[i++];
    }
    s3[idx++] = '\0';
    int val = hash_key(s3);
    if (hash[val] == -1)
    {

        printf("\nSorry, no such trip from %s is available in our bus system. \n \n \n", s3);
        return;
    }
    int flag = 0, j;
    for (j = 1; j <= 100; ++j)
    {
        if (hash[val] == -1)
            break;
        if (strcmp(buses[hash[val]], s3) == 0)
        {
            flag = 1;
            break;
        }
        val++;
        val %= 100;
    }
    if (flag == 0)
    {
        printf("\nSorry, no such trip from %s is available in our bus system. \n  \n \n", s3);
        return;
    }

    int tem;
    printf("\nPress 1 to book ticket. \n");
    printf("Press 2 to cancel ticket. \n");
    printf("Press 3 to show bus information. \n \n");
    printf("Enter your choice: ");
    scanf("%d", &tem);
    printf("\n");
    if (tem == 1)
    {
        bookSeat(hash[val]);
    }
    else if (tem == 2)
    {
        cancel(hash[val]);
    }
    else if (tem == 3)
    {
        showBus(hash[val]);
        return;
    }
    else
    {
        printf("Wrong option has been entered. \n");
        return;
    }
}
int main()
{
    initiate();
    home();
    return 0;
}
