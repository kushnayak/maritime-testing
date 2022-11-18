#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

char str[] = "wrz,0.120,-0.400,2.000,y,1.30,1.855,1e-07;0;1.4;0;1.2;0;0.2;0;1e+09,7,14,123.00,1*50";

void process_velocity() {
    char *token;

    printf("%s\n", str);

    token = strtok(str, ",");   // wrz

    token = strtok(NULL, ",");  // velocity x
    float velocity_x = atof(token);

    token = strtok(NULL, ","); // velocity y 
    float velocity_y = atof(token);


    token = strtok(NULL, ","); // velocity z
    float velocity_z = atof(token);

    token = strtok(NULL, ","); // valid
    bool valid = strcmp(token, "y") == 0;
    
    token = strtok(NULL, ","); // altitude
    float altitude = atof(token);

    token = strtok(NULL, ","); // figure of merit

    // covariance matrix
    for (int i = 0; i < 8; ++i) {
        token = strtok(NULL, ";");
    }
    token = strtok(NULL, ",");

    token = strtok(NULL, ","); // time of validity
    
    token = strtok(NULL, ","); // time of transmission
    
    token = strtok(NULL, ","); // time since last report
    float time_ms = atof(token);

    token = strtok(NULL, "*"); // status
    bool status = strcmp(token, "1") == 0;

    token = strtok(NULL, "\0"); // checksum
    uint16_t checksum = strtol(token, NULL, 16);

    printf("velocity x: %f\ny:%f\nz:%f\nvalid: %d\naltitude: %f\ntime since last: %f\nstatus: %d\nchecksum: 0x%X\n",
            velocity_x, velocity_y, velocity_z, valid, altitude, time_ms, status, checksum);
}

void main(void) {
    process_velocity();
}
