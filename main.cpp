#include "headers.h"
#include "random.h"
#include "data.h"


void readqueue(){
    while(song = mpd_recv_song(conn)){
        queue.push_back(song);
    }
}

bool addsongs(){
    // add whole database to buffer
    if(!mpd_send_list_all(conn, "/")){
        fprintf(stdout, "Could not recieve database data\n");
        return 0;
    }
    // add songs that are not in queue yet in
    readqueue();

    int size = songs.size();
    for(auto song:queue){
        //cout << mpd_song_get_uri(song) << endl; 
        const char *uric = mpd_song_get_uri(song);
        string uri = uric;
        
        if(songs.count(uri)){
            continue;
        }
        
        bool blocked = 0;
        for(auto x:EXCLUDE){ // can be change to Z function for more acurate filtering
            bool flag = 1;
            if(strlen(x)>uri.size()){
                continue;
            }
            for(int i=0;i<strlen(x);i++){
                if(uri[i]!=x[i]){
                    flag = 0;
                    break;
                }
            }
            blocked |= flag;
            if(blocked) break;
        }
        if(blocked) continue;
        size++;
        int idx = range(1,size);
        if(mpd_run_add_id_to(conn, uric, idx)==-1){
           fprintf(stderr, "cannot add %s to %d idx\n", uric, idx);
           return 0;
        }
    }
    
    fprintf(stdout, "Succesfuly added %ld songs\n", size - songs.size());
    return 1;
}

bool getsongs(){
    // add queue to buffer
    if(!mpd_send_list_queue_meta(conn)){
        fprintf(stderr, "Could not recieve queue data\n");
        return 0;
    }
    // get songs in queue
    while(song = mpd_recv_song(conn)){
        string uri = mpd_song_get_uri(song);
        songs.insert(uri);  
    }
    return 1;
}

bool connect(){
    // connect to server
    conn = mpd_connection_new(MPD_HOST, MPD_PORT, MPD_TIMEOUT);
    
    // error handling
    if (conn == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 0;
    }
    if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
        fprintf(stderr, "%s\n", mpd_connection_get_error_message(conn));
        mpd_connection_free(conn);
        return 0;
    }

    // enter password
    if (!mpd_run_password(conn, MPD_PASSWORD)){
        fprintf(stderr, "Incorrect password\n");
        return 0;
    }
    return 1;
}

int main(){
    if(!connect()){
        return 0;
    }
    
    if(!getsongs()){
        return 0;
    }
    
    if(!addsongs()){
        return 0;
    }

    // close the connection and free memory
    mpd_connection_free(conn);
    return 0;
}
