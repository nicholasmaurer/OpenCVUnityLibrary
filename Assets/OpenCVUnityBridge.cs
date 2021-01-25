using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using UnityEngine.Rendering;
using UnityEngine.Tilemaps;

public class OpenCVUnityBridge : MonoBehaviour
{
   [SerializeField] private Texture2D _texture;
    private CommandBuffer _command;

    [DllImport("OPENCVUNITYLIBRARY", EntryPoint = "Init")]
    public static extern int Init();

    [DllImport("OPENCVUNITYLIBRARY", EntryPoint = "GetTextureUpdateCallback")]
    static extern System.IntPtr GetTextureUpdateCallback();
    
    void Start()
    {
        int success = Init();
        Debug.Log(success);
        if (success < 0)
        {
            Debug.Log("Failed to initialize native plugin.");
            return;
        }

        _command = new CommandBuffer();
        _texture = new Texture2D(64, 64, TextureFormat.RGBA32, false);
        _texture.wrapMode = TextureWrapMode.Clamp;
        // Set the texture to the renderer with using a property block.
        var prop = new MaterialPropertyBlock();
        prop.SetTexture("_MainTex", _texture);
        GetComponent<Renderer>().SetPropertyBlock(prop);
    }

    void OnDestroy()
    {
        Destroy(_texture);
        _command.Dispose();
    }

    void Update()
    {
        // Request texture update via the command buffer, to be called on render thread
        _command.IssuePluginCustomTextureUpdateV2(
            GetTextureUpdateCallback(), _texture, (uint) (Time.time * 60)
        ); 
        Graphics.ExecuteCommandBuffer(_command);

        _command.Clear();
        
        // Rotation
        transform.eulerAngles = new Vector3(10, 20, 30) * Time.time;
    }
}
