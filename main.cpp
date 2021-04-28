#include "headers.h"
#include "random.cpp"
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
        int c = 0;
        for(auto x:EXCLUDE){
            if(strlen(x)>uri.size()){
                c++;continue;
            }
            for(int i=0;i<strlen(x);i++){
                if(uri[i]!=x[i]){
                    c++;break;
                }
            }
        }
        if(c!=2) continue;
        if(songs.count(uri))continue;
        size++;
        int idx = range(1,size);
        if(mpd_run_add_id_to(conn, uric, idx)==-1){
           cout << "erno" << endl;
        }
        //cout << idx << " " << id << " " << uri << endl;
    }
    return 1;
}

bool getsongs(){
    // add queue to buffer
    if(!mpd_send_list_queue_meta(conn)){
        fprintf(stdout, "Could not recieve queue data\n");
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
        fprintf(stdout, "Incorrect password\n");
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

 
    // we can now use the connection
    // close the connection and free memory
    mpd_connection_free(conn);
    return 0;
}