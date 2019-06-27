#include <stdio.h>
#include <gst/gst.h>

#include "test.h"

#define TITLE "My Application"
#define TEST_TAG "Gstreamer init"
#define TIME __DATE__,__TIME__

int main(int argc,char *argv[])
{
	print_title();
	//init_menu(argc,argv);
	//gst_init(&argc,&argv);
	//test_element();
	//test_bin();
	//test_bus();
	return 0;
}
static GMainLoop *loop;
static gboolean test_bus_callback(GstBus *bus,GstMessage *message,gpointer data)
{
	printf("Got %s message\n",GST_MESSAGE_TYPE_NAME(message));
	switch(GST_MESSAGE_TYPE(message))
	{
		case GST_MESSAGE_ERROR:
		{
			GError *error;
			char *debug;
			gst_message_parse_error(message,&error,&debug);
			printf("Error: %s\n", error->message);
			g_error_free(error);
			g_main_loop_quit(loop);
			break;
		}
		case GST_MESSAGE_EOS:
			g_main_loop_quit(loop);
			break;
		default:
			printf("default mesaages");
			break;
	}
	return TRUE;
}
int test_bus()
{
	GstElement *pipeline;
	GstBus *bus;
	guint bus_watch_id;

	pipeline=gst_pipeline_new("test_pipeline");
	
	bus=gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	bus_watch_id=gst_bus_add_watch(bus,test_bus_callback,NULL);
	
	loop=g_main_loop_new(NULL,FALSE);
	g_main_loop_run(loop);
	gst_element_set_state(pipeline,GST_STATE_NULL);
	gst_object_unref(pipeline);
	g_source_remove(bus_watch_id);
	g_main_loop_unref(loop);
	return 0;
}
int test_bin()
{
	GstElement *bin, *pipeline, *source, *sink;
	bin=gst_bin_new("test_bin");
	pipeline=gst_pipeline_new("test_pipeline");
	source=gst_element_factory_make("fakesrc","source");
	sink=gst_element_factory_make("fakesink","sink");
	if(!bin||!pipeline||!source||!sink)
	{
		printf("Failed to create some elements\n");
		return -1;
	}
	gst_bin_add_many(GST_BIN(bin),source,sink,NULL);
	gst_bin_add(GST_BIN(pipeline),bin);
	gst_element_link(source,sink);

	gst_element_set_state(GST_ELEMENT(pipeline),GST_STATE_PLAYING);

        //gst_object_unref(GST_OBJECT(bin));
	gst_object_unref(GST_OBJECT(pipeline));
	//gst_object_unref(GST_OBJECT(source));
	//gst_object_unref(GST_OBJECT(sink));
	return 0;
}

int test_element()
{
	GstElementFactory *factory;
	GstElement *element;
	element=gst_element_factory_make("fakesrc","source");
	if(!element)
	{
		printf("Failed to create element of type 'fakesrc'\n");
		return -1;
	}

	printf("use method.1 - success to create element of type 'fakesrc'\n");

	gst_object_unref(GST_OBJECT(element));
	
	factory=gst_element_factory_find("fakesrc");
	if(!factory)
	{
		printf("Failed to find factory of type 'fakesrc'\n");
		return -1;
	}
	element=gst_element_factory_create(factory,"source");
	if(!element)
	{
        	printf("Failed to create element, even though its factory exists!\n");
		return -1;
	}
	printf("use method.2 - success to create element of type 'fakesrc'\n");

	char *name;
	g_object_get(G_OBJECT(element),"name",&name,NULL);
	printf("the element name is %s.\n",name);
	gst_object_unref(GST_OBJECT(factory));
	gst_object_unref(GST_OBJECT(element));
	return 0;
}

int init_menu(int argc,char *argv[])
{
	GOptionContext *context;
	GError *error=NULL;
	gboolean booleanValue=FALSE;
	char *stringValue=NULL;
	GOptionEntry entries[]={
		{"booleanValue",'b',0,G_OPTION_ARG_NONE,&booleanValue,"test bool value",NULL},
		{"stringValue",'s',0,G_OPTION_ARG_STRING,&stringValue,"test string value","string"},
	        {NULL}
	};
	context=g_option_context_new(TITLE);
	g_option_context_add_main_entries(context,entries,NULL);
	g_option_context_add_group(context,gst_init_get_option_group());
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_print ("Failed to initialize: %s\n", error->message);
        g_clear_error (&error);
        g_option_context_free (context);
        return 1;
  }
        g_option_context_free (context);

        printf ("Run me with --help to see the Application options appended.\n");
	return 0;
}
void print_title()
{
	char *nano_str;
        unsigned int major,minor,micro,nano;
        gst_version(&major,&minor,&micro,&nano
);
        if (nano == 1) nano_str = "(CVS)";
        else if (nano == 2) nano_str = "(Prerelease)";                                              else nano_str = "other";
        printf ("This program is linked against GStreamer %d.%d.%d %s\n",major, minor, micro
, nano_str);
	
	printf("==========Gstreamer========\n");                                                    printf("Test:%s\n",TEST_TAG);
        printf("Version:%d.%d.%d\n",GST_VERSION_MAJOR,GST_VERSION_MINOR,GST_VERSION_MICRO);
        printf("Time:%s %s\n",TIME);
	printf ("This program is linked against GStreamer %d.%d.%d %s\n",major, minor, micro, nano_str);
        printf("===========================\n");
}
