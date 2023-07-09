# mysql-ulid-plugin
MySQL UDF Plugin for generating ULIDs

# How to build
## Install mysql_config
For Ubuntu.
```bash
$ sudo apt install libmysqlclient-dev
```

For macOS with homebrew
```bash
$ brew install mysql-connector-c
```

## Build
```bash
$ mkdir build && cd $_
$ cmake ../
$ make
```

## Run test
```bash
$ mysql build && cd $_
$ cmake ../
$ make test
```
or
```bash
$ mysql build && cd $_
$ cmake ../
$ ./ulid-gtest
```

# Use ULID()
```sql
CREATE FUNCTION ulid RETURNS STRING SONAME 'ulid.so';
SELECT ULID();
```
  
Warning: If mysql client run with --binary-as-hex=1, Return string is represent as hex.