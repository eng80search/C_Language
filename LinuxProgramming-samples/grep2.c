/*
    grep2.c

    (EUC-JP encoding)
    �� 8 �Ϥ��������� 1 �β����Ǥ���

    �ʤ������� (����) �ˤ� -v �� -f ���������Ƚ񤤤Ƥ���ޤ���
    ����ϴְ㤤�ǡ��տޤ��Ƥ����Τ� -i ���ץ����Ǥ�����
    �����Ǥ��Υե�����Ǥ� -v, -f, -i �λ��Ĥ�������Ƥ���ޤ���

    ������-f ���ץ������������Ȥ��ˡ����� 8.2 (��)�פΥơ��ޤǤ���
    �Хåե��μ�ư��ĥ��ɬ�פˤʤäƤ��ޤ��ޤ�����read_file() �� 8 ��
    �ޤǤλ����Ǥ�����Ǥ��ʤ��Ȼפ��ޤ��Τǡ�11 �Ϥ� malloc() �Τ�����
    ���ɤ�Ǥ������Ȥ�Ǥ���������
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>

static void grep_file(regex_t *re, char *path);
static void grep_stream(regex_t *re, FILE *f);
static char *read_file(char *path);
static void die(const char *s);

static int opt_invert = 0;
static int opt_ignorecase = 0;

int
main(int argc, char *argv[])
{
    char *pattern = NULL;
    regex_t re;
    int re_mode;
    int err;
    int i;
    int opt;

    while ((opt = getopt(argc, argv, "if:v")) != -1) {
        switch (opt) {
        case 'i':
            opt_ignorecase = 1;
            break;
        case 'f':
            pattern = read_file(optarg);
            break;
        case 'v':
            opt_invert = 1;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-iv] [-f PATTERN] [<file>...]\n", argv[0]);
            exit(1);
        }
    }
    argc -= optind;
    argv += optind;
    if (!pattern) {
        if (argc < 1) {
            fputs("no pattern\n", stderr);
            exit(1);
        }
        pattern = argv[0];
        argc--;
        argv++;
    }

    /* re �ϡ�����ɽ�� (Regular Expression)�פ�ά�졣
       ��regexp�ס�regex�פʤɤ�褯�Ȥ��ޤ� */
    re_mode = REG_EXTENDED | REG_NOSUB | REG_NEWLINE;
    if (opt_ignorecase) re_mode |= REG_ICASE;
    err = regcomp(&re, argv[0], re_mode);
    if (err != 0) {
        char buf[1024];

        regerror(err, &re, buf, sizeof buf);
        puts(buf);
        exit(1);
    }
    if (argc == 0) {
        grep_stream(&re, stdin);
    }
    else {
        for (i = 0; i < argc; i++) {
            grep_file(&re, argv[i]);
        }
    }
    regfree(&re);
    exit(0);
}

/* path �Ǽ������ե������ grep ���� */
static void
grep_file(regex_t *re, char *path)
{
    FILE *f;
    
    f = fopen(path, "r");
    if (!f) {
        perror(path);
        exit(1);
    }
    grep_stream(re, f);
    fclose(f);
}

/* f �Ǽ�����륹�ȥ꡼��� grep ���롣
   ���ҤǤϡ�FILE* �ϥ��ȥ꡼��ʤ�����פȻ������ä������ˡ�
   �ѿ�̾�� f (file ��Ƭʸ��) �ˤ��뤢���꤬�夤�� */
static void
grep_stream(regex_t *re, FILE *f)
{
    char buf[4096];
    int matched;

    while (fgets(buf, sizeof buf, f)) {
        matched = (regexec(re, buf, 0, NULL, 0) == 0);
        if (opt_invert) {
            matched = !matched;
        }
        if (matched) {
            fputs(buf, stdout);
        }
    }
}

/* path �Ǽ������ե�������������Τ��ɤߡ�������֤� */
static char *
read_file(char *path)
{
    FILE *f;
    char *buf;
    size_t capa = 1024;   /* �Хåե������� */
    size_t idx;           /* ���ߤΥХåե��񤭹��߰��� */
    int c;
    
    f = fopen(path, "r");
    if (!f) {
        perror(path);
        exit(1);
    }
    buf = malloc(capa);
    if (!buf) die("malloc");
    while ((c = getc(f)) != EOF) {
        /* �Хåե�Ĺ�����å� ('\0' ������뤳�Ȥ�ͤ��� +1 ����) */
        if (idx + 1 >= capa) {
            capa *= 2;
            buf = realloc(buf, capa);
            if (!buf) die("realloc");
        }
        buf[idx++] = c;
    }
    buf[idx++] = '\0';
    fclose(f);

    return buf;
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
