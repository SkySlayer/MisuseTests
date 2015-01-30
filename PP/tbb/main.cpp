#include <tbb/tbb.h>
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>

#define MAX_STR_LEN 256
struct video_process_object
{
  int video_id;
  char storage_url[MAX_STR_LEN];
  char storage_type[MAX_STR_LEN];
  int face_detect;
  int face_recognise;
  int scene_recognise;
  int activity_recognise;
  int speech_recognise;
};//end struct video_process_object
class InputFilter: public tbb::filter {
  public:
    InputFilter( int );
    ~InputFilter();
  private:
    int total_streams;
    int count;
    struct video_process_object input_obj;
    void* operator()( void* );
};

InputFilter::InputFilter( int x )
  : filter( serial_in_order ) {
    total_streams = x;
    count = 1;
  }

InputFilter::~InputFilter() {
  total_streams = 0;
}

void* InputFilter::operator()( void* ) {
  char path[50] = { };
  sprintf( path, "input//%d.txt", count );
  printf( "Path : %s\n", path );
  FILE *fp;
  fp = fopen( path, "r" );

  if( fp == NULL || count > total_streams ) {
    if(fp != NULL)
        fclose( fp );
    printf( "\n*******Cannot find more data.Terminating********\n\n\n" );
    return NULL;
  }

  fscanf( fp, "%d", &input_obj.video_id );
  fscanf( fp, "%s", input_obj.storage_url );
  fscanf( fp, "%s", input_obj.storage_type );
  fscanf( fp, "%d", &input_obj.face_detect );
  fscanf( fp, "%d", &input_obj.face_recognise );
  fscanf( fp, "%d", &input_obj.scene_recognise );
  fscanf( fp, "%d", &input_obj.activity_recognise );
  fscanf( fp, "%d", &input_obj.speech_recognise );
  fclose( fp );

  count++;
  return &input_obj;
}

class TransformFilter: public tbb::filter {
  public:
    TransformFilter();
    ~TransformFilter();
  private:
    struct video_process_object input_transform;
    void* operator()( void* );
};

TransformFilter::TransformFilter()
  : filter( parallel) {
  }

TransformFilter::~TransformFilter() {
}

void* TransformFilter::operator()( void *item ) {

  input_transform = *static_cast<struct video_process_object*>( item );

  input_transform.video_id += 1000;
  strcat( input_transform.storage_url, "  nabeel" );
  strcat( input_transform.storage_type, " N" );
  input_transform.face_detect += 1000;
  input_transform.face_recognise += 1000;

  return &input_transform;
}

class OutputFilter: public tbb::filter {
  public:
    OutputFilter();
    ~OutputFilter();
  private:
    struct video_process_object output_obj;
    void* operator()( void* );
};

OutputFilter::OutputFilter()
  : filter( serial_in_order ) {
    int status = mkdir( "output", S_IRWXU | S_IRWXG | S_IRWXO );
    if( status == -1 )
      printf( "\nOutput directory already exists\n\n" );
  }

OutputFilter::~OutputFilter() {
}

void* OutputFilter::operator()( void *item ) {

  output_obj = *static_cast<struct video_process_object*>( item );

  FILE *fp;

  char path[50] = { };
  sprintf( path, "output//%d.txt", output_obj.video_id - 1000 );
  printf( "Output Path : %s\t\t %d\n\n", path, output_obj.video_id );

  if( (fp = fopen( path, "w" )) == NULL ) {
    fprintf( stderr, "Cannot open output file.\n" );
    return NULL;
  }

  fprintf( fp, "%d\n", output_obj.video_id );
  fprintf( fp, "%s\n", output_obj.storage_url );
  fprintf( fp, "%s\n", output_obj.storage_type );
  fprintf( fp, "%d\n", output_obj.face_detect );
  fprintf( fp, "%d\n", output_obj.face_recognise );
  fprintf( fp, "%d\n", output_obj.scene_recognise );
  fprintf( fp, "%d\n", output_obj.activity_recognise );
  fprintf( fp, "%d\n", output_obj.speech_recognise );

  fclose( fp );
  return NULL;
}

int main() {
  tbb::pipeline pipeline;

  InputFilter input_filter( 100 );
  pipeline.add_filter( input_filter );

  TransformFilter transform_filter;
  pipeline.add_filter( transform_filter );

  OutputFilter output_filter;
  pipeline.add_filter( output_filter );

  tbb::tick_count t0 = tbb::tick_count::now();

  tbb::task_scheduler_init init_parallel;
  pipeline.run( 8 );
  tbb::tick_count t1 = tbb::tick_count::now();

  return 0;
}
