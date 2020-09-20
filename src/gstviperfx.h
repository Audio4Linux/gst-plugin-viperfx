#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#ifndef __GST_VIPERFX_H__
#define __GST_VIPERFX_H__

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include <gst/audio/audio.h>
#include <gst/audio/gstaudiofilter.h>
#include "viperfx_so.h"


G_BEGIN_DECLS

#define GST_TYPE_VIPERFX            (gst_viperfx_get_type())
#define GST_VIPERFX(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_VIPERFX,Gstviperfx))
#define GST_VIPERFX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass) ,GST_TYPE_VIPERFX,GstviperfxClass))
#define GST_VIPERFX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj) ,GST_TYPE_VIPERFX,GstviperfxClass))
#define GST_IS_VIPERFX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_VIPERFX))
#define GST_IS_VIPERFX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass) ,GST_TYPE_VIPERFX))

#define PACKAGE "viperfx-plugin"
#define VERSION "2.1.0"

#define ALLOWED_CAPS \
  "audio/x-raw,"                            \
  " format=(string){"GST_AUDIO_NE(S16)"},"  \
  " rate=(int)[44100,MAX],"                 \
  " channels=(int)2,"                       \
  " layout=(string)interleaved"

typedef enum {
    PARAM_GROUP_NONE = 0x0000,
    PARAM_GROUP_AGC = (1u << 0),
    PARAM_GROUP_AX = (1u << 1),
    PARAM_GROUP_COLM = (1u << 2),
    PARAM_GROUP_CONV = (1u << 3),
    PARAM_GROUP_CURE = (1u << 4),
    PARAM_GROUP_DS = (1u << 5),
    PARAM_GROUP_DYNSYS = (1u << 6),
    PARAM_GROUP_EQ = (1u << 7),
    PARAM_GROUP_FETCOMP = (1u << 8),
    PARAM_GROUP_LIM = (1u << 9),
    PARAM_GROUP_MSWITCH = (1u << 10),
    PARAM_GROUP_REVERB = (1u << 11),
    PARAM_GROUP_TUBE = (1u << 12),
    PARAM_GROUP_VB = (1u << 13),
    PARAM_GROUP_VC = (1u << 14),
    PARAM_GROUP_VHE = (1u << 15),
    PARAM_GROUP_VSE = (1u << 16),
    PARAM_GROUP_ALL = 0x1FFFF
} PARAM_GROUP;


typedef struct _Gstviperfx      Gstviperfx;
typedef struct _GstviperfxClass GstviperfxClass;

struct _Gstviperfx {
    GstAudioFilter audiofilter;

    /* properties */
    // global enable
    gboolean fx_enabled;
    // Dynamic System
    gboolean dynsys_enabled;
    gint32 dynsys_xcoeffs;
    gint32 dynsys_ycoeffs;
    gint32 dynsys_sidegain;
    gint32 dynsys_xcoeffs2;
    gint32 dynsys_ycoeffs2;
    gint32 dynsys_sidegain2;
    gint32 dynsys_bassgain;
    // convolver
    gboolean conv_enabled;
    gchar *conv_ir_path;
    gint32 conv_cc_level;
    // vhe
    gboolean vhe_enabled;
    gint32 vhe_level;
    // vse
    gboolean vse_enabled;
    gint32 vse_ref_bark;
    gint32 vse_bark_cons;
    // equalizer
    gboolean eq_enabled;
    gint32 eq_band_level[10];
    // colorful music
    gboolean colm_enabled;
    gint32 colm_widening;
    gint32 colm_midimage;
    gint32 colm_depth;
    // diff surr
    gboolean ds_enabled;
    gint32 ds_level;
    // reverb
    gboolean reverb_enabled;
    gint32 reverb_roomsize;
    gint32 reverb_width;
    gint32 reverb_damp;
    gint32 reverb_wet;
    gint32 reverb_dry;
    // agc
    gboolean agc_enabled;
    gint32 agc_ratio;
    gint32 agc_volume;
    gint32 agc_maxgain;
    // viper bass
    gboolean vb_enabled;
    gint32 vb_mode;
    gint32 vb_freq;
    gint32 vb_gain;
    // viper clarity
    gboolean vc_enabled;
    gint32 vc_mode;
    gint32 vc_level;
    // cure
    gboolean cure_enabled;
    gint32 cure_level;
    // tube
    gboolean tube_enabled;
    // analog-x
    gboolean ax_enabled;
    gint32 ax_mode;
    // fet compressor
    gboolean fetcomp_enabled;
    gint32 fetcomp_threshold;
    gint32 fetcomp_ratio;
    gint32 fetcomp_kneewidth;
    gboolean fetcomp_autoknee;
    gint32 fetcomp_gain;
    gboolean fetcomp_autogain;
    gint32 fetcomp_attack;
    gboolean fetcomp_autoattack;
    gint32 fetcomp_release;
    gboolean fetcomp_autorelease;
    gint32 fetcomp_meta_kneemulti;
    gint32 fetcomp_meta_maxattack;
    gint32 fetcomp_meta_maxrelease;
    gint32 fetcomp_meta_crest;
    gint32 fetcomp_meta_adapt;
    gboolean fetcomp_noclip;
    // output volume
    gint32 out_volume;
    // output pan
    gint32 out_pan;
    // limiter
    gint32 lim_threshold;

    /* < private > */
    void *so_handle;
    fn_viperfx_ep so_entrypoint;
    viperfx_interface *vfx;
    GMutex lock;
    guint32 samplerate;
    guint32 dbus_owner_id;
    guint32 sine_sample_counter;
    gint32 sine_duration;
    gint32 sine_frequency;
};

struct _GstviperfxClass {
    GstAudioFilterClass parent_class;
};

GType gst_viperfx_get_type (void);

G_END_DECLS

#endif /* __GST_VIPERFX_H__ */

#pragma clang diagnostic pop