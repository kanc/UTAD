Shader "Custom/grass"
{
    Properties
    {
        _Control ("Control (RGBA)", 2D) = "red" {}
        _Splat3 ("Layer 3 (A)", 2D) = "red" {}
        _Splat2 ("Layer 2 (B)", 2D) = "red" {}
        _Splat1 ("Layer 1 (G)", 2D) = "red" {}
        _Splat0 ("Layer 0 (R)", 2D) = "red" {}
        
        _MainTex ("BaseMap (RGB)", 2D) = "red" {}
        _Color ("Main Color", Color) = (1,1,1,1)
    }

    SubShader
    {
        Tags
        {
            "SplatCount" = "4"
            "Queue" = "Geometry-100"
            "RenderType" = "Opaque"
        }
        Pass
        {
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #include "AutoLight.cginc"
    
            uniform sampler2D _Control;
            uniform float4 _Control_ST;
        
            uniform sampler2D _Splat0,_Splat1,_Splat2,_Splat3;
            uniform float4 _Splat0_ST,_Splat1_ST,_Splat2_ST,_Splat3_ST;
            
            struct appdata
            {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float4 tangent : TANGENT;

                float2 texCoord : TEXCOORD0;
                float2 texCoord1 : TEXCOORD1;
            };
            
            struct v2f
            {
                float4 position : SV_POSITION;
                float2 texCoord : TEXCOORD0;
                float2 texCoord1 : TEXCOORD1;
                
                float3 viewDirTan : TEXCOORD2;
            };
            
            v2f vert(appdata v)
            {
                v2f output;
                
                output.position = mul(UNITY_MATRIX_MVP, v.vertex);
                output.texCoord = TRANSFORM_TEX(v.texCoord, _Splat1);
                output.texCoord1 = TRANSFORM_TEX(v.texCoord1, _Splat2);
                output.texCoord1.x += _Time * 1.4;
                output.texCoord1.y += _Time * 0.5;
				
              
                // This is a regular grid so the we just pick a tangent along the x-axis
                v.tangent = float4(1, 0, 0, -1);
                float3 viewDir = WorldSpaceViewDir(v.vertex);
                TANGENT_SPACE_ROTATION;
                output.viewDirTan = normalize(mul(rotation, viewDir));
                
                return output;
            }
            
            #define GRASS_HEIGHT_SCALAR 0.005
            #define OFFSET_SCALAR           0.004
            #define OFFSET_SCALAR_HALF   0.002
            #define GRASS_THICKNESS        0.5
            #define NUM_LAYERS                4
            
            half4 frag(v2f input) : COLOR
            {
                float3 rayEntry = float3(input.texCoord.xy, 0.0);
            
                float4 color = float4(0, 0, 0, 0);
                
                int layer;
                for (layer = 0; layer < NUM_LAYERS - 1; layer++)
                {
                    float distance = (layer * GRASS_HEIGHT_SCALAR) / -input.viewDirTan.z;
                    float3 hitpoint = rayEntry + (input.viewDirTan * distance);
                    
                    float2 offset = tex2D(_Splat2, input.texCoord1);
                    offset = offset - 0.5;
                    offset *= (NUM_LAYERS - layer) * OFFSET_SCALAR;
                    hitpoint += float3(offset.x, offset.y, 0);
                    
                    float4 lookup = tex2D(_Splat0, hitpoint.xy / GRASS_THICKNESS);
                    float srcAlpha = lookup.r;
                    float dstAlpha = 1.0 - color.a;
                    
                    float3 normal = normalize(float3(offset.x, OFFSET_SCALAR_HALF, offset.y));
                    float diffuse = 1.0 - (dot(normal, float3(0.37, -0.93, 0))); // hardcoded sunlight vector. we should grab this from unity
                    float alphaMix = srcAlpha * dstAlpha;
                
                    color.rgb += tex2D(_Splat1, hitpoint.xy) * alphaMix * diffuse;
                    color.a += alphaMix;
                }
                
                // We actually do the last (ground) layer outside the loop
                // Here we ignore the look up texture and take whatever the ground color is
                // multiplied by some factor so it's not too bright.
                //
                float dstAlpha = (1.0 - color.a) * 0.6;
                float distance = (NUM_LAYERS * GRASS_HEIGHT_SCALAR) / -input.viewDirTan.z;
                float3 hitpoint = rayEntry + (input.viewDirTan * distance);
                color.rgb += tex2D(_Splat1, hitpoint.xy) * dstAlpha;
                color.a += dstAlpha;
                
                return color;
            }
    
            ENDCG
        }
    }
}