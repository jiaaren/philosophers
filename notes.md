initialising threads
- why doesn't this work?
  - seg faults
  - mem leaks

        while (i < p_num)
        {
            pthread_create(&(tmp[i++]), NULL, test_thread, NULL);
            pthread_join(tmp[i++], NULL);
        }

- but this does?

        while (i < p_num)
            pthread_create(&(tmp[i++]), NULL, test_thread, NULL);
        i = 0;
        while (i < p_num)
            pthread_join(tmp[i++], NULL);